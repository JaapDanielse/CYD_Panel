// Layouts.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// (Panel::Layouts)

//-------------------------------------------------------------------------------------
void CYD_Panel::MonitorLayout()
{
	this->O_MonitorField_1 = Display{ 20,  40, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	this->O_MonitorField_2 = Display{ 20,  70, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	this->O_MonitorField_3 = Display{ 20, 100, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	this->O_MonitorField_4 = Display{ 20, 130, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	this->O_MonitorField_5 = Display{ 20, 160, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	this->O_MonitorField_6 = Display{ 20, 190, 280, 20, CYD_NoOverlay, CYD_MONITOR };
	
	this->O_MonitorField_1.CYD_Visible(true);	
	this->O_MonitorField_2.CYD_Visible(true);	
	this->O_MonitorField_3.CYD_Visible(true);	
	this->O_MonitorField_4.CYD_Visible(true);	
	this->O_MonitorField_5.CYD_Visible(true);	
	this->O_MonitorField_6.CYD_Visible(true);	

	this->O_MonitorField_1.CYD_Color(TFT_BLACK); 
	this->O_MonitorField_2.CYD_Color(TFT_BLACK); 
	this->O_MonitorField_3.CYD_Color(TFT_BLACK); 
	this->O_MonitorField_4.CYD_Color(TFT_BLACK); 
	this->O_MonitorField_5.CYD_Color(TFT_BLACK); 
	this->O_MonitorField_6.CYD_Color(TFT_BLACK); 

	this->O_MonitorField_1.CYD_BGColor(TFT_LIGHTGREY); 
	this->O_MonitorField_2.CYD_BGColor(TFT_LIGHTGREY); 
	this->O_MonitorField_3.CYD_BGColor(TFT_LIGHTGREY); 
	this->O_MonitorField_4.CYD_BGColor(TFT_LIGHTGREY); 
	this->O_MonitorField_5.CYD_BGColor(TFT_LIGHTGREY); 
	this->O_MonitorField_6.CYD_BGColor(TFT_LIGHTGREY); 

	PanelElements[CYD_MonitorField_1]  = &this->O_MonitorField_1;
	PanelElements[CYD_MonitorField_2]  = &this->O_MonitorField_2;
	PanelElements[CYD_MonitorField_3]  = &this->O_MonitorField_3;
	PanelElements[CYD_MonitorField_4]  = &this->O_MonitorField_4;
	PanelElements[CYD_MonitorField_5]  = &this->O_MonitorField_5;
	PanelElements[CYD_MonitorField_6]  = &this->O_MonitorField_6;
}

//-------------------------------------------------------------------------------------
void CYD_Panel::InfoLayout()
{
	this->O_InfoPanel = TextPanel{ 20,  40, 280, 180, CYD_NoOverlay, CYD_INFO };
	PanelElements[CYD_InfoPanel]  = &this->O_InfoPanel;
	this->O_InfoPanel.CYD_Visible(true);
}

//-------------------------------------------------------------------------------------
void CYD_Panel::HeaderLayout()
{
	this->O_MButton_1 = Button(  0, 0, 20, 20, CYD_NoOverlay, CYD_ALL);
	this->O_MButton_2 = Button( 22, 0, 20, 20, CYD_NoOverlay, CYD_ALL);
	this->O_MButton_3 = Button( 44, 0, 20, 20, CYD_NoOverlay, CYD_ALL);
	PanelElements[CYD_MButton_1]  = &this->O_MButton_1;
	PanelElements[CYD_MButton_2]  = &this->O_MButton_2;
	PanelElements[CYD_MButton_3]  = &this->O_MButton_3;
	this->O_MButton_1.CYD_Visible(true);
	this->O_MButton_2.CYD_Visible(true);
	this->O_MButton_3.CYD_Visible(true);

  this->O_ApplicationName = Display( 80, 0, 220, 20, CYD_NoOverlay, CYD_ALL);
	PanelElements[CYD_ApplicationName] = &this->O_ApplicationName;
	this->O_ApplicationName.CYD_BGColor(TFT_DARKGREY); 
}

//-------------------------------------------------------------------------------------
void CYD_Panel::Layout_1()
{
  // display panel (provides black backdrop for displays and graphs)
	this->O_DisplayPanel = Display( 0, 20, 320, 116 ); // black display backdrop
	this->O_DisplayPanel.CYD_Visible(true); // must be visible
	PanelElements[CYD_DisplayPanel]  = &this->O_DisplayPanel; // add pointer in PanelElements array
	
  // right displays (1-4)	
	this->O_Display_1 = Display( 20,  20, 280, 29, CYD_Display_5); // re-constuct for this layout
	this->O_Display_2 = Display( 20,  49, 280, 29, CYD_Display_6);
	this->O_Display_3 = Display( 20,  78, 280, 29, CYD_Display_7);
	this->O_Display_4 = Display( 20, 107, 280, 29, CYD_Display_8);
	PanelElements[CYD_Display_1]  = &this->O_Display_1; // add pointer in PanelElements array
	PanelElements[CYD_Display_2]  = &this->O_Display_2;
	PanelElements[CYD_Display_3]  = &this->O_Display_3;
	PanelElements[CYD_Display_4]  = &this->O_Display_4;

  // left displays (5-8)
	this->O_Display_5 = Display(  20,  20, 140, 29);
	this->O_Display_6 = Display(  20,  49, 140, 29);
	this->O_Display_7 = Display(  20,  78, 140, 29);
	this->O_Display_8 = Display(  20, 107, 140, 29);
	PanelElements[CYD_Display_5]  = &this->O_Display_5;
	PanelElements[CYD_Display_6]  = &this->O_Display_6;
	PanelElements[CYD_Display_7]  = &this->O_Display_7;
	PanelElements[CYD_Display_8]  = &this->O_Display_8;
	
	// graph panels (overlapping display panel)
	this->O_Graph_1 = Graph( 0, 20, 320, 116);
	this->O_Graph_2 = Graph( 0, 20, 320, 116);
	this->O_Graph_3 = Graph( 0, 20, 320, 116);
	PanelElements[CYD_Graph_1]  = &this->O_Graph_1;
	PanelElements[CYD_Graph_2]  = &this->O_Graph_2;
	PanelElements[CYD_Graph_3]  = &this->O_Graph_3;
	
  // buttons top row (1-6)
	this->O_Button_1 = Button(  0, 136, 50, 50, CYD_Led_1);
	this->O_Button_2 = Button( 54, 136, 50, 50, CYD_Led_2);
	this->O_Button_3 = Button(108, 136, 50, 50, CYD_Led_3);
	this->O_Button_4 = Button(162, 136, 50, 50, CYD_Led_4);
	this->O_Button_5 = Button(216, 136, 50, 50, CYD_Led_5);
	this->O_Button_6 = Button(270, 136, 50, 50, CYD_Led_6);
	PanelElements[CYD_Button_1]  = &this->O_Button_1;
	PanelElements[CYD_Button_2]  = &this->O_Button_2;
	PanelElements[CYD_Button_3]  = &this->O_Button_3;
	PanelElements[CYD_Button_4]  = &this->O_Button_4;
	PanelElements[CYD_Button_5]  = &this->O_Button_5;
	PanelElements[CYD_Button_6]  = &this->O_Button_6;

  // sliders overlapping buttons 1-6
	this->O_Slider_1  = Slider(  1, 136, 105, 50);
	this->O_Slider_2  = Slider(109, 136, 105, 50);
	this->O_Slider_3  = Slider(216, 136, 105, 50);
	PanelElements[CYD_Slider_1] = &this->O_Slider_1;
	PanelElements[CYD_Slider_2] = &this->O_Slider_2;
	PanelElements[CYD_Slider_3] = &this->O_Slider_3;

  // buttons bottom row (7-12)
	this->O_Button_7  = Button(  0, 190, 50, 50, CYD_Led_7);
	this->O_Button_8  = Button( 54, 190, 50, 50, CYD_Led_8);
	this->O_Button_9  = Button(108, 190, 50, 50, CYD_Led_9);
	this->O_Button_10 = Button(162, 190, 50, 50, CYD_Led_10);
	this->O_Button_11 = Button(216, 190, 50, 50, CYD_Led_11);
	this->O_Button_12 = Button(270, 190, 50, 50, CYD_Led_12);
	PanelElements[CYD_Button_7]  = &this->O_Button_7;
	PanelElements[CYD_Button_8]  = &this->O_Button_8;
	PanelElements[CYD_Button_9]  = &this->O_Button_9;
	PanelElements[CYD_Button_10] = &this->O_Button_10;
	PanelElements[CYD_Button_11] = &this->O_Button_11;
	PanelElements[CYD_Button_12] = &this->O_Button_12;

  // sliders overlapping buttons 7-12
	this->O_Slider_4  = Slider(  0, 190, 105, 50);
	this->O_Slider_5  = Slider(108, 190, 105, 50);
	this->O_Slider_6  = Slider(216, 190, 105, 50);
	PanelElements[CYD_Slider_4] = &this->O_Slider_4;
	PanelElements[CYD_Slider_5] = &this->O_Slider_5;
	PanelElements[CYD_Slider_6] = &this->O_Slider_6;

  // led's on button 1-6
	this->O_Led_1  = Led( 17, 136, 16, 6);
	this->O_Led_2  = Led( 71, 136, 16, 6);
	this->O_Led_3  = Led(125, 136, 16, 6);
	this->O_Led_4  = Led(179, 136, 16, 6);
	this->O_Led_5  = Led(233, 136, 16, 6);
	this->O_Led_6  = Led(287, 136, 16, 6);
	PanelElements[CYD_Led_1]  = &this->O_Led_1;
	PanelElements[CYD_Led_2]  = &this->O_Led_2;
	PanelElements[CYD_Led_3]  = &this->O_Led_3;
	PanelElements[CYD_Led_4]  = &this->O_Led_4;
	PanelElements[CYD_Led_5]  = &this->O_Led_5;
	PanelElements[CYD_Led_6]  = &this->O_Led_6;

  // led's on button 7-12
	this->O_Led_7  = Led( 17, 190, 16, 6);
	this->O_Led_8  = Led( 71, 190, 16, 6);
	this->O_Led_9  = Led(125, 190, 16, 6);
	this->O_Led_10 = Led(179, 190, 16, 6);
	this->O_Led_11 = Led(233, 190, 16, 6);
	this->O_Led_12 = Led(287, 190, 16, 6);
	PanelElements[CYD_Led_7]  = &this->O_Led_7;
	PanelElements[CYD_Led_8]  = &this->O_Led_8;
	PanelElements[CYD_Led_9]  = &this->O_Led_9;
	PanelElements[CYD_Led_10] = &this->O_Led_10;
	PanelElements[CYD_Led_11] = &this->O_Led_11;
	PanelElements[CYD_Led_12] = &this->O_Led_12;

  // led's right of displays 1-4
	this->O_Led_13 = Led(304,  31, 16, 6);
	this->O_Led_14 = Led(304,  60, 16, 6);
	this->O_Led_15 = Led(304,  89, 16, 6);
	this->O_Led_16 = Led(304, 118, 16, 6);
	PanelElements[CYD_Led_13] = &this->O_Led_13;
	PanelElements[CYD_Led_14] = &this->O_Led_14;
	PanelElements[CYD_Led_15] = &this->O_Led_15;
	PanelElements[CYD_Led_16] = &this->O_Led_16;

  // led's left of displays 5-8
	this->O_Led_17 = Led(  0,  31, 16, 6);
	this->O_Led_18 = Led(  0,  60, 16, 6);
	this->O_Led_19 = Led(  0,  89, 16, 6);
	this->O_Led_20 = Led(  0, 118, 16, 6);
	PanelElements[CYD_Led_17] = &this->O_Led_17;
	PanelElements[CYD_Led_18] = &this->O_Led_18;
	PanelElements[CYD_Led_19] = &this->O_Led_19;
	PanelElements[CYD_Led_20] = &this->O_Led_20;
}

//-------------------------------------------------------------------------------------
void CYD_Panel::Layout_2()
{
  // display panel (provides black backdrop for displays and graphs)
	this->O_DisplayPanel = Display( 0, 20, 320, 170 );
	this->O_DisplayPanel.CYD_Visible(true); // must be visible
	PanelElements[CYD_DisplayPanel]  = &this->O_DisplayPanel;
	
  // right displays (1-4)	
	this->O_Display_1 = Display( 20,  20, 280, 34, CYD_Display_6);
	this->O_Display_2 = Display( 20,  54, 280, 34, CYD_Display_7);
	this->O_Display_3 = Display( 20,  88, 280, 34, CYD_Display_8);
	this->O_Display_4 = Display( 20, 122, 280, 34, CYD_Display_9);
	this->O_Display_5 = Display( 20, 156, 280, 34, CYD_Display_10);
	PanelElements[CYD_Display_1]  = &this->O_Display_1;
	PanelElements[CYD_Display_2]  = &this->O_Display_2;
	PanelElements[CYD_Display_3]  = &this->O_Display_3;
	PanelElements[CYD_Display_4]  = &this->O_Display_4;
	PanelElements[CYD_Display_5]  = &this->O_Display_5;

  // left displays (5-8)
	this->O_Display_6  = Display( 20,  20, 140, 34);
	this->O_Display_7  = Display( 20,  54, 140, 34);
	this->O_Display_8  = Display( 20,  88, 140, 34);
	this->O_Display_9  = Display( 20, 122, 140, 34);
	this->O_Display_10 = Display( 20, 156, 140, 34);
	PanelElements[CYD_Display_6]  = &this->O_Display_6;
	PanelElements[CYD_Display_7]  = &this->O_Display_7;
	PanelElements[CYD_Display_8]  = &this->O_Display_8;
	PanelElements[CYD_Display_9]  = &this->O_Display_9;
	PanelElements[CYD_Display_10] = &this->O_Display_10;
	
	// graph panels (overlapping display panel)
	this->O_Graph_1 = Graph( 0, 20, 320, 170);
	this->O_Graph_2 = Graph( 0, 20, 320, 170);
	this->O_Graph_3 = Graph( 0, 20, 320, 170);
	PanelElements[CYD_Graph_1]  = &this->O_Graph_1;
	PanelElements[CYD_Graph_2]  = &this->O_Graph_2;
	PanelElements[CYD_Graph_3]  = &this->O_Graph_3;
	
  // buttons top row (1-6)
	this->O_Button_1 = Button(  0, 190, 50, 50, CYD_Led_1);
	this->O_Button_2 = Button( 54, 190, 50, 50, CYD_Led_2);
	this->O_Button_3 = Button(108, 190, 50, 50, CYD_Led_3);
	this->O_Button_4 = Button(162, 190, 50, 50, CYD_Led_4);
	this->O_Button_5 = Button(216, 190, 50, 50, CYD_Led_5);
	this->O_Button_6 = Button(270, 190, 50, 50, CYD_Led_6);
	PanelElements[CYD_Button_1]  = &this->O_Button_1;
	PanelElements[CYD_Button_2]  = &this->O_Button_2;
	PanelElements[CYD_Button_3]  = &this->O_Button_3;
	PanelElements[CYD_Button_4]  = &this->O_Button_4;
	PanelElements[CYD_Button_5]  = &this->O_Button_5;
	PanelElements[CYD_Button_6]  = &this->O_Button_6;

  // sliders overlapping buttons 1-6
	this->O_Slider_1  = Slider(  1, 190, 105, 50);
	this->O_Slider_2  = Slider(109, 190, 105, 50);
	this->O_Slider_3  = Slider(216, 190, 105, 50);
	PanelElements[CYD_Slider_1] = &this->O_Slider_1;
	PanelElements[CYD_Slider_2] = &this->O_Slider_2;
	PanelElements[CYD_Slider_3] = &this->O_Slider_3;

  // led's on button 1-6
	this->O_Led_1  = Led( 17, 190, 16, 6);
	this->O_Led_2  = Led( 71, 190, 16, 6);
	this->O_Led_3  = Led(125, 190, 16, 6);
	this->O_Led_4  = Led(179, 190, 16, 6);
	this->O_Led_5  = Led(233, 190, 16, 6);
	this->O_Led_6  = Led(287, 190, 16, 6);
	PanelElements[CYD_Led_1]  = &this->O_Led_1;
	PanelElements[CYD_Led_2]  = &this->O_Led_2;
	PanelElements[CYD_Led_3]  = &this->O_Led_3;
	PanelElements[CYD_Led_4]  = &this->O_Led_4;
	PanelElements[CYD_Led_5]  = &this->O_Led_5;
	PanelElements[CYD_Led_6]  = &this->O_Led_6;

  // led's left of displays 5-8
	this->O_Led_7  = Led(  0,  34, 16, 6);
	this->O_Led_8  = Led(  0,  68, 16, 6);
	this->O_Led_9  = Led(  0, 102, 16, 6);
	this->O_Led_10 = Led(  0, 136, 16, 6);
	this->O_Led_11 = Led(  0, 170, 16, 6);
	PanelElements[CYD_Led_7]  = &this->O_Led_7;
	PanelElements[CYD_Led_8]  = &this->O_Led_8;
	PanelElements[CYD_Led_9]  = &this->O_Led_9;
	PanelElements[CYD_Led_10] = &this->O_Led_10;
	PanelElements[CYD_Led_11] = &this->O_Led_11;

  // led's right of displays 1-3
	this->O_Led_12 = Led(304,  34, 16, 6);
	this->O_Led_13 = Led(304,  68, 16, 6);
	this->O_Led_14 = Led(304, 102, 16, 6);
	this->O_Led_15 = Led(304, 136, 16, 6);
	this->O_Led_16 = Led(304, 170, 16, 6);
	PanelElements[CYD_Led_12] = &this->O_Led_12;
	PanelElements[CYD_Led_13] = &this->O_Led_13;
	PanelElements[CYD_Led_14] = &this->O_Led_14;
	PanelElements[CYD_Led_15] = &this->O_Led_15;
	PanelElements[CYD_Led_16] = &this->O_Led_16;
}

//-------------------------------------------------------------------------------------
void CYD_Panel::Layout_3()
{
  // display panel (provides black backdrop for displays and graphs)
	this->O_DisplayPanel = Display( 0, 20, 320, 62 );
	this->O_DisplayPanel.CYD_Visible(true); // must be visible
	PanelElements[CYD_DisplayPanel]  = &this->O_DisplayPanel;
	
  // right displays (1-4)	
	this->O_Display_1 = Display( 20,  20, 280, 31, CYD_Display_3);
	this->O_Display_2 = Display( 20,  49, 280, 31, CYD_Display_4);
	PanelElements[CYD_Display_1]  = &this->O_Display_1;
	PanelElements[CYD_Display_2]  = &this->O_Display_2;

  // left displays (5-8)
	this->O_Display_3 = Display(  20,  20, 140, 31);
	this->O_Display_4 = Display(  20,  49, 140, 31);
	PanelElements[CYD_Display_3]  = &this->O_Display_3;
	PanelElements[CYD_Display_4]  = &this->O_Display_4;
	
	// graph panels (overlapping display panel)
	this->O_Graph_1 = Graph( 0, 20, 320, 62);
	this->O_Graph_2 = Graph( 0, 20, 320, 62);
	this->O_Graph_3 = Graph( 0, 20, 320, 62);
	PanelElements[CYD_Graph_1]  = &this->O_Graph_1;
	PanelElements[CYD_Graph_2]  = &this->O_Graph_2;
	PanelElements[CYD_Graph_3]  = &this->O_Graph_3;
	
  // buttons top row (1-6)
	this->O_Button_1 = Button(  0, 82, 50, 50, CYD_Led_1);
	this->O_Button_2 = Button( 54, 82, 50, 50, CYD_Led_2);
	this->O_Button_3 = Button(108, 82, 50, 50, CYD_Led_3);
	this->O_Button_4 = Button(162, 82, 50, 50, CYD_Led_4);
	this->O_Button_5 = Button(216, 82, 50, 50, CYD_Led_5);
	this->O_Button_6 = Button(270, 82, 50, 50, CYD_Led_6);
	PanelElements[CYD_Button_1]  = &this->O_Button_1;
	PanelElements[CYD_Button_2]  = &this->O_Button_2;
	PanelElements[CYD_Button_3]  = &this->O_Button_3;
	PanelElements[CYD_Button_4]  = &this->O_Button_4;
	PanelElements[CYD_Button_5]  = &this->O_Button_5;
	PanelElements[CYD_Button_6]  = &this->O_Button_6;

  // sliders overlapping buttons 1-6
	this->O_Slider_1  = Slider(  1, 82, 105, 50);
	this->O_Slider_2  = Slider(109, 82, 105, 50);
	this->O_Slider_3  = Slider(216, 82, 105, 50);
	PanelElements[CYD_Slider_1] = &this->O_Slider_1;
	PanelElements[CYD_Slider_2] = &this->O_Slider_2;
	PanelElements[CYD_Slider_3] = &this->O_Slider_3;

  // buttons middle row (7-12)
	this->O_Button_7  = Button(  0, 136, 50, 50, CYD_Led_7);
	this->O_Button_8  = Button( 54, 136, 50, 50, CYD_Led_8);
	this->O_Button_9  = Button(108, 136, 50, 50, CYD_Led_9);
	this->O_Button_10 = Button(162, 136, 50, 50, CYD_Led_10);
	this->O_Button_11 = Button(216, 136, 50, 50, CYD_Led_11);
	this->O_Button_12 = Button(270, 136, 50, 50, CYD_Led_12);
	PanelElements[CYD_Button_7]  = &this->O_Button_7;
	PanelElements[CYD_Button_8]  = &this->O_Button_8;
	PanelElements[CYD_Button_9]  = &this->O_Button_9;
	PanelElements[CYD_Button_10] = &this->O_Button_10;
	PanelElements[CYD_Button_11] = &this->O_Button_11;
	PanelElements[CYD_Button_12] = &this->O_Button_12;

  // sliders overlapping buttons 7-12
	this->O_Slider_4  = Slider(  0, 136, 105, 50);
	this->O_Slider_5  = Slider(108, 136, 105, 50);
	this->O_Slider_6  = Slider(216, 136, 105, 50);
	PanelElements[CYD_Slider_4] = &this->O_Slider_4;
	PanelElements[CYD_Slider_5] = &this->O_Slider_5;
	PanelElements[CYD_Slider_6] = &this->O_Slider_6;

  // buttons bottom row (13-18)
	this->O_Button_13 = Button(  0, 190, 50, 50, CYD_Led_13);
	this->O_Button_14 = Button( 54, 190, 50, 50, CYD_Led_14);
	this->O_Button_15 = Button(108, 190, 50, 50, CYD_Led_15);
	this->O_Button_16 = Button(162, 190, 50, 50, CYD_Led_16);
	this->O_Button_17 = Button(216, 190, 50, 50, CYD_Led_17);
	this->O_Button_18 = Button(270, 190, 50, 50, CYD_Led_18);
	PanelElements[CYD_Button_13] = &this->O_Button_13;
	PanelElements[CYD_Button_14] = &this->O_Button_14;
	PanelElements[CYD_Button_15] = &this->O_Button_15;
	PanelElements[CYD_Button_16] = &this->O_Button_16;
	PanelElements[CYD_Button_17] = &this->O_Button_17;
	PanelElements[CYD_Button_18] = &this->O_Button_18;

  // sliders overlapping buttons 7-12
	this->O_Slider_7  = Slider(  0, 190, 105, 50);
	this->O_Slider_8  = Slider(108, 190, 105, 50);
	this->O_Slider_9  = Slider(216, 190, 105, 50);
	PanelElements[CYD_Slider_7] = &this->O_Slider_7;
	PanelElements[CYD_Slider_8] = &this->O_Slider_8;
	PanelElements[CYD_Slider_9] = &this->O_Slider_9;

  // led's on button 1-6
	this->O_Led_1  = Led( 17, 82, 16, 6);
	this->O_Led_2  = Led( 71, 82, 16, 6);
	this->O_Led_3  = Led(125, 82, 16, 6);
	this->O_Led_4  = Led(179, 82, 16, 6);
	this->O_Led_5  = Led(233, 82, 16, 6);
	this->O_Led_6  = Led(287, 82, 16, 6);
	PanelElements[CYD_Led_1]  = &this->O_Led_1;
	PanelElements[CYD_Led_2]  = &this->O_Led_2;
	PanelElements[CYD_Led_3]  = &this->O_Led_3;
	PanelElements[CYD_Led_4]  = &this->O_Led_4;
	PanelElements[CYD_Led_5]  = &this->O_Led_5;
	PanelElements[CYD_Led_6]  = &this->O_Led_6;

  // led's on button 7-12
	this->O_Led_7  = Led( 17, 136, 16, 6);
	this->O_Led_8  = Led( 71, 136, 16, 6);
	this->O_Led_9  = Led(125, 136, 16, 6);
	this->O_Led_10 = Led(179, 136, 16, 6);
	this->O_Led_11 = Led(233, 136, 16, 6);
	this->O_Led_12 = Led(287, 136, 16, 6);
	PanelElements[CYD_Led_7]  = &this->O_Led_7;
	PanelElements[CYD_Led_8]  = &this->O_Led_8;
	PanelElements[CYD_Led_9]  = &this->O_Led_9;
	PanelElements[CYD_Led_10] = &this->O_Led_10;
	PanelElements[CYD_Led_11] = &this->O_Led_11;
	PanelElements[CYD_Led_12] = &this->O_Led_12;

  // led's on button 13-18
	this->O_Led_13 = Led( 17, 190, 16, 6);
	this->O_Led_14 = Led( 71, 190, 16, 6);
	this->O_Led_15 = Led(125, 190, 16, 6);
	this->O_Led_16 = Led(179, 190, 16, 6);
	this->O_Led_17 = Led(233, 190, 16, 6);
	this->O_Led_18 = Led(287, 190, 16, 6);
	PanelElements[CYD_Led_13] = &this->O_Led_13;
	PanelElements[CYD_Led_14] = &this->O_Led_14;
	PanelElements[CYD_Led_15] = &this->O_Led_15;
	PanelElements[CYD_Led_16] = &this->O_Led_16;
	PanelElements[CYD_Led_17] = &this->O_Led_17;
	PanelElements[CYD_Led_18] = &this->O_Led_18;

  // led's left of displays 3-4
	this->O_Led_19 = Led(  0,  31, 16, 6);
	this->O_Led_20 = Led(  0,  60, 16, 6);
	PanelElements[CYD_Led_19] = &this->O_Led_19;
	PanelElements[CYD_Led_20] = &this->O_Led_20;

  // led's right of displays 1-2
	this->O_Led_21 = Led(304,  31, 16, 6);
	this->O_Led_22 = Led(304,  60, 16, 6);
	PanelElements[CYD_Led_21] = &this->O_Led_21;
	PanelElements[CYD_Led_22] = &this->O_Led_22;
}

//-------------------------------------------------------------------------------------
void CYD_Panel::Layout_4()
{
  // display panel (provides black backdrop for displays and graphs)
	this->O_DisplayPanel = Display( 0, 20, 270, 170 );
	this->O_DisplayPanel.CYD_Visible(true); // must be visible
	PanelElements[CYD_DisplayPanel]  = &this->O_DisplayPanel;
	
  // right displays (1-4)	
	this->O_Display_1 = Display( 20,  20, 226, 34, CYD_Display_6);
	this->O_Display_2 = Display( 20,  54, 226, 34, CYD_Display_7);
	this->O_Display_3 = Display( 20,  88, 226, 34, CYD_Display_8);
	this->O_Display_4 = Display( 20, 122, 226, 34, CYD_Display_9);
	this->O_Display_5 = Display( 20, 156, 226, 34, CYD_Display_10);
	PanelElements[CYD_Display_1]  = &this->O_Display_1;
	PanelElements[CYD_Display_2]  = &this->O_Display_2;
	PanelElements[CYD_Display_3]  = &this->O_Display_3;
	PanelElements[CYD_Display_4]  = &this->O_Display_4;
	PanelElements[CYD_Display_5]  = &this->O_Display_5;

  // left displays (6-10)	
	this->O_Display_6  = Display( 20,  20, 113, 34);
	this->O_Display_7  = Display( 20,  54, 113, 34);
	this->O_Display_8  = Display( 20,  88, 113, 34);
	this->O_Display_9  = Display( 20, 122, 113, 34);
	this->O_Display_10 = Display( 20, 156, 113, 34);
	PanelElements[CYD_Display_6]   = &this->O_Display_6;
	PanelElements[CYD_Display_7]   = &this->O_Display_7;
	PanelElements[CYD_Display_8]   = &this->O_Display_8;
	PanelElements[CYD_Display_9]   = &this->O_Display_9;
	PanelElements[CYD_Display_10]  = &this->O_Display_10;

	// graph panels (overlapping display panel)
	this->O_Graph_1 = Graph( 0, 20, 270, 170);
	this->O_Graph_2 = Graph( 0, 20, 270, 170);
	this->O_Graph_3 = Graph( 0, 20, 270, 170);
	PanelElements[CYD_Graph_1]  = &this->O_Graph_1;
	PanelElements[CYD_Graph_2]  = &this->O_Graph_2;
	PanelElements[CYD_Graph_3]  = &this->O_Graph_3;
	
  // buttons row (1-6)
	this->O_Button_1 = Button(  0, 190, 50, 50, CYD_Led_1);
	this->O_Button_2 = Button( 54, 190, 50, 50, CYD_Led_2);
	this->O_Button_3 = Button(108, 190, 50, 50, CYD_Led_3);
	this->O_Button_4 = Button(162, 190, 50, 50, CYD_Led_4);
	this->O_Button_5 = Button(216, 190, 50, 50, CYD_Led_5);
	this->O_Button_6 = Button(270, 190, 50, 50, CYD_Led_6);
	PanelElements[CYD_Button_1]  = &this->O_Button_1;
	PanelElements[CYD_Button_2]  = &this->O_Button_2;
	PanelElements[CYD_Button_3]  = &this->O_Button_3;
	PanelElements[CYD_Button_4]  = &this->O_Button_4;
	PanelElements[CYD_Button_5]  = &this->O_Button_5;
	PanelElements[CYD_Button_6]  = &this->O_Button_6;

  // sliders overlapping buttons 1-6
	this->O_Slider_1  = Slider(  1, 190, 105, 50);
	this->O_Slider_2  = Slider(109, 190, 105, 50);
	this->O_Slider_3  = Slider(216, 190, 105, 50);
	PanelElements[CYD_Slider_1] = &this->O_Slider_1;
	PanelElements[CYD_Slider_2] = &this->O_Slider_2;
	PanelElements[CYD_Slider_3] = &this->O_Slider_3;

  // led's on button 1-6
	this->O_Led_1  = Led( 17, 190, 16, 6);
	this->O_Led_2  = Led( 71, 190, 16, 6);
	this->O_Led_3  = Led(125, 190, 16, 6);
	this->O_Led_4  = Led(179, 190, 16, 6);
	this->O_Led_5  = Led(233, 190, 16, 6);
	this->O_Led_6  = Led(287, 190, 16, 6);
	PanelElements[CYD_Led_1]  = &this->O_Led_1;
	PanelElements[CYD_Led_2]  = &this->O_Led_2;
	PanelElements[CYD_Led_3]  = &this->O_Led_3;
	PanelElements[CYD_Led_4]  = &this->O_Led_4;
	PanelElements[CYD_Led_5]  = &this->O_Led_5;
	PanelElements[CYD_Led_6]  = &this->O_Led_6;
	
	  // buttons (7-9)
	this->O_Button_7 = Button(270,  20, 50, 50, CYD_Led_7);
	this->O_Button_8 = Button(270,  76, 50, 50, CYD_Led_8);
	this->O_Button_9 = Button(270, 133, 50, 50, CYD_Led_9);
	PanelElements[CYD_Button_7] = &this->O_Button_7;
	PanelElements[CYD_Button_8] = &this->O_Button_8;
	PanelElements[CYD_Button_9] = &this->O_Button_9;
	
  // led's on button 7-9
	this->O_Led_7 = Led(287,  20, 16, 6);
	this->O_Led_8 = Led(287,  76, 16, 6);
	this->O_Led_9 = Led(287, 133, 16, 6);
	PanelElements[CYD_Led_7] = &this->O_Led_7;
	PanelElements[CYD_Led_8] = &this->O_Led_8;
	PanelElements[CYD_Led_9] = &this->O_Led_9;

  // led's left of displays 1-5
	this->O_Led_10 = Led(  0,  34, 16, 6);
	this->O_Led_11 = Led(  0,  68, 16, 6);
	this->O_Led_12 = Led(  0, 102, 16, 6);
	this->O_Led_13 = Led(  0, 136, 16, 6);
	this->O_Led_14 = Led(  0, 170, 16, 6);
	PanelElements[CYD_Led_10] = &this->O_Led_10;
	PanelElements[CYD_Led_11] = &this->O_Led_11;
	PanelElements[CYD_Led_12] = &this->O_Led_12;
	PanelElements[CYD_Led_13] = &this->O_Led_13;
	PanelElements[CYD_Led_14] = &this->O_Led_14;

  // led's right of displays 1-5
	this->O_Led_15 = Led(251,  34, 16, 6);
	this->O_Led_16 = Led(251,  68, 16, 6);
	this->O_Led_17 = Led(251, 102, 16, 6);
	this->O_Led_18 = Led(251, 136, 16, 6);
	this->O_Led_19 = Led(251, 170, 16, 6);
	PanelElements[CYD_Led_15] = &this->O_Led_15;
	PanelElements[CYD_Led_16] = &this->O_Led_16;
	PanelElements[CYD_Led_17] = &this->O_Led_17;
	PanelElements[CYD_Led_18] = &this->O_Led_18;
	PanelElements[CYD_Led_19] = &this->O_Led_19;
}

