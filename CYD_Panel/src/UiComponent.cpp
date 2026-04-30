// UIComponent.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// UIComponent (UI base class)

//-------------------------------------------------------------------------------------
void UIComponent::CYD_Visible(bool visible) // set visible
{
	_visible = visible;
  if(!_visible)	tft.fillRect(_x, _y, _w, _h, Panel._panelcolor); // becoming invisible: remove component;
	this->CYD_Draw(false);
}

//-------------------------------------------------------------------------------------
void  UIComponent::CYD_Font(uint16_t font) {}
	
//-------------------------------------------------------------------------------------
void  UIComponent::CYD_BGColor(uint16_t color) {}



