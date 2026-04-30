// Button.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// Button

//-------------------------------------------------------------------------------------
void Button::CYD_Color(uint16_t color)
{
	_color = color;
	this->CYD_Draw(true);  
}

//-------------------------------------------------------------------------------------
void  Button::CYD_BGColor(uint16_t color) 
{
	_bgcolor = color;
	this->CYD_Draw(true);  
}

//-------------------------------------------------------------------------------------
void  Button::CYD_Font(uint16_t font) 
{
	_font = font;
	this->CYD_Draw(true);  
}

//-------------------------------------------------------------------------------------
void Button::CYD_Draw(bool update)
{
  if(_inUse && _visible)
 { 
		tft.fillRect(_x, _y, _w, _h, _bgcolor); 
		WriteText(_x, _y, _w, _h, _color, _font, _text, true); 
			
		if(_overlay == CYD_NoOverlay) return;
		if(Panel.PanelElements[(int)_overlay] == nullptr) return;
		Panel.PanelElements[(int)_overlay]->CYD_Draw(false);
	}
}

//-------------------------------------------------------------------------------------
void Button::CYD_HandleMessage(CYD_param param, CYD_type type)
{
	if(_inUse)
	{
		// string
		if(param == CYD_NOPARAM && type == CYD_string)
    {
			if(strlen(Panel.cyds_string) >= BUTTON_TXT_BUFFER_SIZE) 
			{
				strncpy(_text, Panel.cyds_string, BUTTON_TXT_BUFFER_SIZE-1); 
				_text[BUTTON_TXT_BUFFER_SIZE-1] = 0;
			}
			else
			{	stpcpy(_text, Panel.cyds_string); }
			
			this->CYD_Visible(true);
		}
		
		// font
		if(param == CYD_FONT && type == CYD_byte)
		{
			this->CYD_Font(Panel.cyds_byte); 
		}

		// text color
		if(param == CYD_COLOR && type == CYD_byte)
		{
			this->CYD_Color(CYD_TFT_Colors[Panel.cyds_byte]);
		}
		
		// back color
		if(param == CYD_BACKCOLOR && type == CYD_byte)
		{
			this->CYD_BGColor(CYD_TFT_Colors[Panel.cyds_byte]);
		}

		// visible
		if(param == CYD_NOPARAM && type == CYD_boolean)
		{
			this->CYD_Visible(Panel.cyds_boolean);
		}
	}
}

//-------------------------------------------------------------------------------------
uint16_t Button::CYD_HandleClick(int x, int y, bool c) 
{
	if(!_inUse || !_visible) return false;

	if(x >= _x && x <= _x + _w && y >= _y && y <= _y + _h)
	{
	  Panel.cydr_type = CYD_void;
  	if(c) return 150; else return 500;
	}
	else
		return 0;
}
