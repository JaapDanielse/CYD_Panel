// Graph.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// Graph

//-------------------------------------------------------------------------------------
void Graph::CYD_Color(uint16_t color)
{
	_color = color;
}

//-------------------------------------------------------------------------------------
void  Graph::CYD_BGColor(uint16_t color) 
{
	_bgcolor = color;
}

//-------------------------------------------------------------------------------------
void Graph::CYD_Draw(bool clear)
{
	uint16_t _ox = _x;
	uint16_t _oy = 0;
	uint16_t _cx = 0;
	uint16_t _cy = 0;
	uint16_t margin = 0;
	
	
  if(_inUse && _visible)
	{
    margin = (_w % (_valueCount - 1)) / 2;

		_ox = _x + margin;
		_oy = _y + _h - 1 - _values[0];

		for(uint16_t i = 1; i < _valueIdx; i++)
		{
			_cx = _x + margin + (i * (_w / (_valueCount - 1)));
			_cy = _y + _h - 1 - _values[i];
			
      if(clear)
				tft.drawLine(_ox, _oy, _cx, _cy, _bgcolor);
			else
				tft.drawLine(_ox, _oy, _cx, _cy, _color);
			
			_ox = _cx;
			_oy = _cy;

		}
	}
}

//-------------------------------------------------------------------------------------
void Graph::CYD_HandleMessage(CYD_param param, CYD_type type)
{
	if(_inUse)
	{
		// value
		if(param == CYD_NOPARAM && type == CYD_byte)
		{
			if(_rolling)
			{
				this->CYD_Draw(true); // remove previous line
				
				if(_valueIdx < _valueCount) 
					_values[_valueIdx++] = map(Panel.cyds_byte, 0, 255, 0, _h-1);
				else
				{
					for(uint16_t i = 1; i <	_valueCount; i++)
					{
						_values[i-1] = _values[i];
					}
					_values[_valueIdx - 1] = map(Panel.cyds_byte, 0, 255, 0, _h-1);
				}

				_visible = true;
				this->CYD_Draw(false); // draw new line
			}
			else // Static (!Rolling)
			{
				if(_valueIdx < _valueCount)
				{
					_values[_valueIdx + (MAX_GRAPH_VALUE_COUNT / 2)] = map(Panel.cyds_byte, 0, 255, 0, _h-1);
					_valueIdx++;
				}
				else
				{
					this->CYD_Draw(true); // remove previous line

					for(uint16_t i = 0; i <	_valueCount; i++)
					{
						_values[i] = _values[i + (MAX_GRAPH_VALUE_COUNT / 2)];
					}
					_visible = true;
					this->CYD_Draw(false); // draw new line
					_valueIdx = 0;
					_values[_valueIdx + (MAX_GRAPH_VALUE_COUNT / 2)] = map(Panel.cyds_byte, 0, 255, 0, _h-1);
					_valueIdx++;
				}
			}
		}  

		// count
		if(param == CYD_VALUECOUNT && type == CYD_int)
		{
			if(_rolling)
			{
				if(Panel.cyds_int <= MAX_GRAPH_VALUE_COUNT)
			  {	_valueCount = Panel.cyds_int; }
			  else 
			  {	_valueCount = MAX_GRAPH_VALUE_COUNT; }
			}
			else
			{
				if(Panel.cyds_int <= MAX_GRAPH_VALUE_COUNT / 2)
			  {	_valueCount = Panel.cyds_int; }
			  else 
			  {	_valueCount = MAX_GRAPH_VALUE_COUNT / 2; }
			}
		}

		if(param == CYD_VALUECOUNT && type == CYD_long)
		{
			if(_rolling)
			{
				if(Panel.cyds_int <= MAX_GRAPH_VALUE_COUNT)
			  {	_valueCount = (int16_t) Panel.cyds_long; }
			  else 
			  {	_valueCount = MAX_GRAPH_VALUE_COUNT; }
			}
			else
			{
				if(Panel.cyds_int <= MAX_GRAPH_VALUE_COUNT / 2)
			  {	_valueCount = (int16_t) Panel.cyds_long; }
			  else 
			  {	_valueCount = MAX_GRAPH_VALUE_COUNT / 2; }
			}
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
		
		// rolling
		if(param == CYD_ROLLING && type == CYD_void)
		{
			_rolling = true;
			_valueIdx = 0;
			for(uint16_t i = 1; i <	MAX_GRAPH_VALUE_COUNT; i++)  { _values[i] = 0; }
		}		

		// static 
		if(param == CYD_STATIC && type == CYD_void)
		{
			_rolling = false;
			_valueIdx = 0;
			for(uint16_t i = 1; i <	MAX_GRAPH_VALUE_COUNT; i++)  { _values[i] = 0; }
			if(_valueCount > MAX_GRAPH_VALUE_COUNT / 2) _valueCount = MAX_GRAPH_VALUE_COUNT / 2;
		}

		// clear
		if(param == CYD_CLEAR && type == CYD_void)
		{
			this->CYD_Draw(true); // remove previous line
			_valueIdx = 0;
			for(uint16_t i = 1; i <	MAX_GRAPH_VALUE_COUNT; i++)  { _values[i] = 0; }
		}
		
		// visible
		if(param == CYD_NOPARAM && type == CYD_boolean)
		{
			if(!Panel.cyds_boolean)
			{
				this->CYD_Draw(true); // remove previous line
			}
			this->_visible = Panel.cyds_boolean;
		}
	}
}

//-------------------------------------------------------------------------------------
uint16_t Graph::CYD_HandleClick(int x, int y, bool c) 
{
	return 0;
}

