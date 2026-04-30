// Led.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// Led

//-------------------------------------------------------------------------------------
void Led::CYD_Color(uint16_t color)
{
	_color = color;
	this->CYD_Visible(true);
}

//-------------------------------------------------------------------------------------
void Led::CYD_Draw(bool update)
{
	if(_inUse && _visible)
	{
		tft.fillRect(_x, _y, _w, _h, _color);
  }
}


//-------------------------------------------------------------------------------------
void Led::CYD_HandleMessage(CYD_param param, CYD_type type)
{
	if(_inUse)
	{	
		// color
		if(param == CYD_COLOR && type == CYD_byte)
		{
			this->CYD_Color(CYD_TFT_Colors[Panel.cyds_byte]);
		}

		// visible
		if(param == CYD_NOPARAM && type == CYD_boolean)
		{
			this->CYD_Visible(Panel.cyds_boolean);
		}
  }
}

//-------------------------------------------------------------------------------------
uint16_t Led::CYD_HandleClick(int x, int y, bool c) 
{
	return 0;
}

