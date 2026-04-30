// Slider.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
//Slider

// Constructor ------------------------------------------------------------------------
Slider::Slider (uint16_t x, uint16_t y, uint16_t w, uint16_t h, CYD_channel overlay, CYD_screen screen) : UIComponent (x, y, w, h, overlay, screen)
{
	_scx = _x + 12; // slider control x (0)
	_scy = _y; // slider control y 
	_scw = 30; // slider control width
	_sch = 30; // slider control height 
	_scRange = _w - _scw - (2 * 12); // original width - control width - step width * 2 (<>)
  _scxMin = _scx; // min absolute control x pos (0)
	_scxMax = _scx + _scRange;  // max absolute control x pos (max)

}

//-------------------------------------------------------------------------------------
void Slider::CYD_Value(uint16_t value)
{
	if(value <= _maxValue) 
	{
		_value = value;
    _scx = _scxMin + (uint16_t) (((float)_value / (float)_maxValue) * (float)_scRange);
		
		this->CYD_Draw(false); 
  }
}

//-------------------------------------------------------------------------------------
void Slider::CYD_Color(uint16_t color)
{
	_color = color;
	this->CYD_Draw(false);  
}

//-------------------------------------------------------------------------------------
void  Slider::CYD_BGColor(uint16_t color) 
{
	
	_slidercolor = color;
	// _bgcolor = color;
	this->CYD_Draw(false);  
}

//-------------------------------------------------------------------------------------
void  Slider::CYD_Font(uint16_t font) 
{
	_font = font;
	this->CYD_Draw(false);  
}

//-------------------------------------------------------------------------------------
void Slider::CYD_Draw(bool update)
{
  if(_inUse)
	{
		if(_visible)
		{ 
			tft.fillRect(_x, _y, _w, _h - 20, _bgcolor); // slider background top 30 px
			WriteText(_x, _y, 10, _h - 20, _color, _font, "<", true); // one step left
			WriteText(_x + _w - 10 , _y, 10, _h - 20, _color, _font, ">", true); // one step right
			WriteText(_x, _y + 30, _w, _h - 30, _color, _font, _text, true); //slider text 20 px below
			tft.fillRect(_scx, _scy,_scw, _sch, _slidercolor); // slider control
		}
	}
}

//-------------------------------------------------------------------------------------
void Slider::CYD_HandleMessage(CYD_param param, CYD_type type)
{
	if(_inUse)
	{
    // value
		if(param == CYD_NOPARAM && type == CYD_int)
		{
			this->CYD_Value(Panel.cyds_int); 
		}
		
		if(param == CYD_NOPARAM && type == CYD_long)
		{
			this->CYD_Value((int16_t) Panel.cyds_long); 
		}
		
    // MaxValue
		if(param == CYD_MAXVALUE && type == CYD_int)
		{
			_maxValue = Panel.cyds_int;
		}
		
		if(param == CYD_MAXVALUE && type == CYD_long)
		{
			_maxValue = (int16_t) Panel.cyds_long;
		}

		// string: label
		if(param == CYD_NOPARAM && type == CYD_string)
		{
			if(strlen(Panel.cyds_string) >= BUTTON_TXT_BUFFER_SIZE) 
			{
				strncpy(_text, Panel.cyds_string, BUTTON_TXT_BUFFER_SIZE-1); 
				_text[BUTTON_TXT_BUFFER_SIZE-1] = 0;
			}
			else
			{	
				stpcpy(_text, Panel.cyds_string); 
			}
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
uint16_t Slider::CYD_HandleClick(int x, int y, bool c) 
{
	if(_inUse && _visible)
	{
		if(x >= _x && x <= (_x + _w) && y >= _y && y <= (_y + _h - 20)) // within the slider area?
		{
			// left of slider control (-1)
			if(x < _scx) 
			{
				this->CYD_Value(_value - 1);
				Panel.cydr_int = _value;
				if(c) return 150; else return 500;		
			}

			// right of slider control (-1)
			if(x > (_scx + 30)) 
			{
				this->CYD_Value(_value + 1);
				Panel.cydr_int = _value;
				if(c) return 150; else return 500;		
			}
			
			// in slider control
			if(x >= _scx && x <= (_scx + 30)) 
			{
				_scx = x - 16;
				
				if(_scx < _scxMin) _scx = _scxMin;
				if(_scx > _scxMax) _scx = _scxMax;
				
				_value = (uint16_t) (((float)(_scx - _scxMin) / (float) _scRange) * (float) _maxValue);
				
				if(_scx != _scxOld)
				{
					_scxOld = _scx;
					Panel.cydr_type = CYD_int;
					Panel.cydr_int = _value;

					this->CYD_Draw(false);
					return 25;
				}
			}		
		}
	}
	return 0;		
}

