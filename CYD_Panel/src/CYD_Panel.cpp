// CYD_Panel.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//-------------------------------------------------------------------------------------
// Class instantiation Panel, TFT, Touchscreen

TFT_eSPI tft = TFT_eSPI();
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ); //

CYD_Panel Panel(PanelCallback); // instantiation of the Panel object

//-------------------------------------------------------------------------------------
// Panel will be running on core 0 (started from Panel.begin() )
TaskHandle_t Task1;

void Task1code( void * pvParameters )
{
  Serial.print("Panel Handling Core ");
  Serial.println(xPortGetCoreID());
	
	for(;;)
	{
    Panel.GetScreenTouch();
		Panel.HandleSend();
    delay(5);
	}
}


//=====================================================================================
// CYD_Panel 

//-------------------------------------------------------------------------------------
// Constructor
CYD_Panel::CYD_Panel(PanelCallbackFunction CallBackPointer) : _CallBackPointer(CallBackPointer)
{ }


//-------------------------------------------------------------------------------------
void CYD_Panel::begin(CYD_layout layout)
{
	touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
	touchscreen.begin(touchscreenSPI);
	touchscreen.setRotation(1); // Set the Touchscreen rotation in landscape mode (3) upside down

	tft.init(); // Start the tft display
	tft.setRotation(1); // Set the TFT display rotation in landscape mode
	tft.invertDisplay(1);
	tft.fillScreen(_panelcolor); // Clear the screen before writing to it
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	
	
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    2048,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  Serial.print("User code Core ");
  Serial.println(xPortGetCoreID());
	
  while(cyds_sent) {}
	
	Panel.cyds_channel = CYD_Reset;
  Panel.cyds_type = CYD_byte;
	Panel.cyds_byte = (uint8_t) layout;
	cyds_sent = true; 	
}


//-------------------------------------------------------------------------------------
void CYD_Panel::reset(CYD_layout layout)
{
	for(uint8_t i = 0; i < CYD_EndChannel; i++)
	{
		if(PanelElements[i]) this->PanelElements[i]->_inUse = false;
		PanelElements[i] = nullptr;
  }
	
	HeaderLayout();
	switch(layout)
	{
		case CYD_LAYOUT_1: Layout_1(); break;
		case CYD_LAYOUT_2: Layout_2(); break;
		case CYD_LAYOUT_3: Layout_3(); break;
		case CYD_LAYOUT_4: Layout_4(); break;
		default: return;
	}
	
  MonitorLayout();
  InfoLayout();

  setScreen(CYD_HOME);
	
	cydr_channel = CYD_PanelConnected;
	cydr_received = true;
}


//-------------------------------------------------------------------------------------
void CYD_Panel::setScreen(CYD_screen screen)
{
	tft.fillScreen(_panelcolor); // Clear the screen before writing to it

	for(uint8_t i = 0; i < CYD_EndChannel; i++) 
	{
		if(PanelElements[i])
		{ 
			if(this->PanelElements[i]->_screen == screen || this->PanelElements[i]->_screen == CYD_ALL) 
			{
				this->PanelElements[i]->_inUse = true;
				this->PanelElements[i]->CYD_Draw(false);
			}
			else
				this->PanelElements[i]->_inUse = false;
		}
  }
	this->O_MButton_1.CYD_BGColor(TFT_LIGHTGREY);
	this->O_MButton_2.CYD_BGColor(TFT_LIGHTGREY);
	this->O_MButton_3.CYD_BGColor(TFT_LIGHTGREY);
	if(screen == CYD_HOME) this->O_MButton_1.CYD_BGColor(0xE73C);
	if(screen == CYD_MONITOR) this->O_MButton_2.CYD_BGColor(0xE73C);
	if(screen == CYD_INFO) this->O_MButton_3.CYD_BGColor(0xE73C);
}


//-------------------------------------------------------------------------------------
void CYD_Panel::GetScreenTouch()
{
	uint16_t x = 0;
	uint16_t y = 0;
	static bool c = false;
	static uint32_t receiveTimer = 0;
	uint16_t rdelay = 0;
	//uint16_t z = 0;
	
	if(receiveTimer > millis()) return;
	
	if (!touchscreen.tirqTouched()) return;

	if(touchscreen.touched()) 
	{
		// Get Touchscreen points
		TS_Point p = touchscreen.getPoint();
		// Calibrate Touchscreen points with map function to the correct width and height
		x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
		y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
		//z = p.z;

		for(int16_t i = CYD_EndUI + 1 ; i >= 0; i--) // from bottom to top 
		{
			if (PanelElements[i] != nullptr) 
			{
				rdelay = PanelElements[i]->CYD_HandleClick(x, y, c);
				if(rdelay)
				{
					cydr_channel = (CYD_channel) i;
					c = true;
					receiveTimer = millis() + rdelay;
					break;
				}
			}
		}
		if(rdelay)
		{
		 			 if(cydr_channel == CYD_MButton_1) setScreen(CYD_HOME);
			else if(cydr_channel == CYD_MButton_2) setScreen(CYD_MONITOR);
			else if(cydr_channel == CYD_MButton_3) setScreen(CYD_INFO);
		  else cydr_received = true;
	  }	
	}
	else
	{
		c = false;
  	receiveTimer = millis() + 25;
	}	
}	


//-------------------------------------------------------------------------------------
void CYD_Panel::HandleSend()
{
  if(cyds_sent)
	{
   	if(cyds_channel == CYD_Reset)
    {			
				Panel.reset((CYD_layout) cyds_byte);
    }
		else if(PanelElements[(int)cyds_channel] != nullptr)
    {
				this->PanelElements[(int)cyds_channel]->CYD_HandleMessage(cyds_param, cyds_type);
		}
		cyds_sent = false; 
  }
}


//-------------------------------------------------------------------------------------
void CYD_Panel::receive()
{
  if(cydr_received)
	{
    _CallBackPointer(cydr_channel);
  	cydr_received = false;	
  }
}

//SENDF ===========
// channel with char* ...
//-------------------------------------------------------------------------------------
void CYD_Panel::sendf(CYD_channel channel, const char* message, ...)
{
	while(cyds_sent);
	
	static char buf[SENDFBUFFERSIZE];
	va_list args;
	va_start(args, message);
	vsnprintf(buf, SENDFBUFFERSIZE, message, args);
	va_end(args);	

	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_string;
	Panel.cyds_string = buf;
	cyds_sent = true; 
}


// SEND ===========
// channel with char*
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, const char* message)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_string;
	Panel.cyds_string = message;
	cyds_sent = true; 
}

// channel with byte value
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, uint8_t value)
{
	while(cyds_sent);
		
	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_byte;
	Panel.cyds_byte = value;
	cyds_sent = true; 
}

// channel with int16_t value
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, int16_t value)
{
	while(cyds_sent);

	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_int;
	Panel.cyds_int = value;
	cyds_sent = true; 
}

// channel with int value
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, int value)
{
	CYD_Panel::send(channel, (int32_t)value);
}

// channel with int32_t value
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, int32_t value)
{
	while(cyds_sent);

	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_long;
	Panel.cyds_long = value;
	cyds_sent = true; 
}

// chanel with parameter (_MaxValue, _ValueCount) and int16_t value 
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, int16_t value)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_int;
	Panel.cyds_int = value;
	cyds_sent = true; 
}

// chanel with parameter (_MaxValue, _ValueCount) and int value 
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, int value)
{
	CYD_Panel::send(channel, param, (int32_t)value);
}

// chanel with parameter (_MaxValue, _ValueCount) and int32_t value 
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, int32_t value)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_long;
	Panel.cyds_long = value;
	cyds_sent = true; 
}

// channel with (void) parameter (_Clear)
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param)
{
	while(cyds_sent);

	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_void;
	cyds_sent = true; 
}

// channel parameter (_Color, _BackColor) and color 
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, CYD_color colorId)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_byte;
	Panel.cyds_byte = colorId;
	cyds_sent = true; 	
}

// channel with parameter (_Font) and font
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, CYD_font fontId)
{
	while(cyds_sent);

	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_byte;
	Panel.cyds_byte = fontId;
	cyds_sent = true; 	
}

// channel (InfoPanel) with param (_InfoTitle) and string
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_param param, const char* message)
{
	while(cyds_sent);

	Panel.cyds_channel = channel;
	Panel.cyds_param = param;
  Panel.cyds_type = CYD_string;
	Panel.cyds_string = message;
	cyds_sent = true; 	
}

// channel with parameter and boolean (true = visible, false = invisible)
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, bool visible)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_boolean;
	Panel.cyds_boolean = visible;
	cyds_sent = true; 	
}

// channel (Reset) and layout
//-------------------------------------------------------------------------------------
void CYD_Panel::send(CYD_channel channel, CYD_layout layoutId)
{
	while(cyds_sent);
	
	Panel.cyds_channel = channel;
	Panel.cyds_param = CYD_NOPARAM;
  Panel.cyds_type = CYD_byte;
	Panel.cyds_byte = (uint8_t) layoutId;
	cyds_sent = true; 	
}

