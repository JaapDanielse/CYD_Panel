// TextPanel.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// TextPanel

//-------------------------------------------------------------------------------------
void TextPanel::CYD_Color(uint16_t color)
{
	_color = color;
	this->CYD_Visible(true);
}

//-------------------------------------------------------------------------------------
void TextPanel::CYD_Draw(bool update)
{
	if(_inUse && _visible)
	{
		tft.setTextColor(TFT_WHITE);
			if(_TextLinePtr[0] != nullptr) 
				tft.drawString(_TextLinePtr[0], _x, _y, 2);
		
		tft.setTextColor(_color);
		for(int i=1; i < 12; i++)
		{
			if(_TextLinePtr[i] != nullptr) 
				tft.drawString(_TextLinePtr[i], _x, _y + (i * 14) + 20, 1);
		}	
  }
}

//-------------------------------------------------------------------------------------
void TextPanel::CYD_HandleMessage(CYD_param param, CYD_type type)
{
	if(param == CYD_NOPARAM && type == CYD_string)
	{
  	_TextLinePtr[_TextLineIdx] = Panel.cyds_string;
	  if(++_TextLineIdx == 12)  _TextLineIdx = 0;
	}

	if(param == CYD_TITLE && type == CYD_string)
	{
  	_TextLinePtr[0] = Panel.cyds_string;
		for(int i=1; i < 12; i++)
		{
			_TextLinePtr[i] = nullptr; 
		}	
		_TextLineIdx = 1;
	}
}

//-------------------------------------------------------------------------------------
uint16_t TextPanel::CYD_HandleClick(int x, int y, bool c) 
{
	return 0;
}



