// CYD_Panel H_RGB_Led_Control example - Documentation https://github.com/JaapDanielse/CYD_Panel/wiki/Basic-Examples
// GNU Licence - Copyright (c) 2026 Jaap Danielse - https://github.com/JaapDanielse/CYD_Panel

#include "CYD_Panel.h"

const uint8_t RedPin   =  4; // define the RGB led pins
const uint8_t GreenPin = 16; 
const uint8_t BluePin  = 17;

uint8_t Red = 0; // 
uint8_t Blue = 0;
uint8_t Green = 0;

bool Power = false; // Power status

//-----------------------------------------------------------------------------
void setup() 
{
  Panel.begin(); // start the panel 
  pinMode(RedPin, OUTPUT); // set the RGB Led pins as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
}

//-----------------------------------------------------------------------------
void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

//-----------------------------------------------------------------------------
void PanelCallback(CYD_channel event) 
{ 
  switch (event) // switch on the events
  {
    case CYD_PanelConnected:
      Panel.send(CYD_ApplicationName,"RGB Led Control"); // Set the application name
      Panel.send(CYD_Button_12,"on/off"); // set the text on button 12
      Panel.send(CYD_Led_12, CYD_COLOR, CYD_BLACK); // set led 12 (button 12)
      Panel.send(CYD_Slider_1, CYD_MAXVALUE, 255); // set slider 1 max value
      Panel.send(CYD_Slider_1, CYD_BACKCOLOR, CYD_RED); // set slider 1 back color (looks pretty)
      Panel.send(CYD_Slider_1,"Red"); // set slider 1 text (and make it visible)
      Panel.send(CYD_Slider_2, CYD_MAXVALUE, 255); // ...
      Panel.send(CYD_Slider_2, CYD_BACKCOLOR, CYD_GREEN); 
      Panel.send(CYD_Slider_2,"Green");
      Panel.send(CYD_Slider_3, CYD_MAXVALUE, 255);
      Panel.send(CYD_Slider_3, CYD_BACKCOLOR, CYD_BLUE);
      Panel.send(CYD_Slider_3,"Blue");
     break;

    case CYD_Button_12:
      Power = !Power; // toggle power
     break;
    case CYD_Slider_1:
      Red = Panel.cydr_int; // get the slider value for red
      break;
    case CYD_Slider_2:
      Green = Panel.cydr_int; // get the slider value for green
      break;
    case CYD_Slider_3:
      Blue = Panel.cydr_int; // get the slider value for blue
      break;

    default: break;
  }

  // this gets executed for all events
  if(Power)
  { // Power is on
    Panel.send(CYD_Led_12, CYD_COLOR, CYD_RED); // set led 12 to red
    analogWrite(RedPin, 255-Red); // output to the led pins (255 is off)
    analogWrite(BluePin, 255-Blue);
    analogWrite(GreenPin, 255-Green);
  }
  else
  { // power is off
    Panel.send(CYD_Led_12, CYD_COLOR, CYD_BLACK); // set led 12 to black
    analogWrite(RedPin, 255); // turn the rgb led off (255 is off)
    analogWrite(BluePin, 255);
    analogWrite(GreenPin, 255);
  }

  Panel.sendf(CYD_Display_2, "Red: %03d       Green: %03d       Blue: %03d ", Red, Green, Blue );
}

