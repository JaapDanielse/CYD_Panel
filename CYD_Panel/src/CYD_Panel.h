/*
  CYD_Panel.h
  MIT Licence - Copyright (c) 2026 Jaap Danielse - https://github.com/JaapDanielse/CYD_Panel

  CYD_Panel is an Arduino libray to implement a simple UI tool for experiment and prototyping on the Cheap Yellow display.
  CYD_Panel is built on top of the TFT_eSPI library by Bodmer: https://github.com/Bodmer/TFT_eSPI,
  and the XPT2046_Touchscreen library by Paul Stoffregen: https://github.com/PaulStoffregen/XPT2046_Touchscreen.
  Next to this instructions form Random Nerd Tutorials for getting started with CYD: https://randomnerdtutorials.com/cheap-yellow-display-esp32-2432s028r/ 
  were used aswell as their User_Setup.h (see instructions)

  V1.0.0 03-05-2026 Initial Version

*/

#pragma once

#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// Touchscreen pins
#define XPT2046_IRQ  36 // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 39 // T_OUT
#define XPT2046_CLK  25 // T_CLK
#define XPT2046_CS   33 // T_CS

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2

#define SENDFBUFFERSIZE 60 // Buffersize for formatted text sendf
#define RECEIVEBUFFERSIZE 60 // Buffersize for pannel events: 60 + 5 (msg overhead)
#define BUTTON_TXT_BUFFER_SIZE 30 //
#define DISPLAY_TXT_BUFFER_SIZE 60 //
#define MAX_GRAPH_VALUE_COUNT 160 //


enum CYD_layout : uint8_t
{
	CYD_LAYOUT_1,
	CYD_LAYOUT_2,
	CYD_LAYOUT_3,
	CYD_LAYOUT_4
};

enum CYD_channel : uint8_t
{
	CYD_ApplicationName, // 0
	CYD_DisplayPanel, // 1
	CYD_Display_1,  //  2
	CYD_Display_2,  //  3
	CYD_Display_3,  //  4
	CYD_Display_4,  //  5
	CYD_Display_5,  //  6
	CYD_Display_6,  //  7
	CYD_Display_7,  //  8
	CYD_Display_8,  //  9
	CYD_Display_9,  // 10
	CYD_Display_10, // 11
	CYD_Graph_1,   // 12
	CYD_Graph_2,   // 13
	CYD_Graph_3,   // 14
	CYD_Button_1,  // 15
	CYD_Button_2,  // 16
	CYD_Button_3,  // 17
	CYD_Button_4,  // 18
	CYD_Button_5,  // 19
	CYD_Button_6,  // 20
	CYD_Button_7,  // 21
	CYD_Button_8,  // 22
	CYD_Button_9,  // 23
	CYD_Button_10, // 24
	CYD_Button_11, // 25
	CYD_Button_12, // 26
	CYD_Button_13, // 27
	CYD_Button_14, // 28
	CYD_Button_15, // 29
	CYD_Button_16, // 30
	CYD_Button_17, // 31
	CYD_Button_18, // 32
	CYD_Slider_1, // 33
	CYD_Slider_2, // 34
	CYD_Slider_3, // 35
	CYD_Slider_4, // 36
	CYD_Slider_5, // 37
	CYD_Slider_6, // 38
	CYD_Slider_7, // 39
	CYD_Slider_8, // 40
	CYD_Slider_9, // 41
	CYD_Led_1,  // 42
	CYD_Led_2,  // 43
	CYD_Led_3,  // 44
	CYD_Led_4,  // 45
	CYD_Led_5,  // 46
	CYD_Led_6,  // 47
	CYD_Led_7,  // 48
	CYD_Led_8,  // 49
	CYD_Led_9,  // 50
	CYD_Led_10, // 51
	CYD_Led_11, // 52
	CYD_Led_12, // 53
	CYD_Led_13, // 54
	CYD_Led_14, // 55
	CYD_Led_15, // 56
	CYD_Led_16, // 57
	CYD_Led_17, // 58
	CYD_Led_18, // 59
	CYD_Led_19, // 60
	CYD_Led_20, // 61
	CYD_Led_21, // 62
	CYD_Led_22, // 63
	CYD_MonitorField_1, // 64
	CYD_MonitorField_2, // 65
	CYD_MonitorField_3, // 66
	CYD_MonitorField_4, // 67
	CYD_MonitorField_5, // 68
	CYD_MonitorField_6, // 69
	CYD_InfoPanel, // 70
	CYD_MButton_1, // 71
	CYD_MButton_2, // 72
	CYD_MButton_3, // 73
	CYD_EndUI, // 74 - above here only UI components
	CYD_PanelConnected, // 75
	CYD_Reset, // 76
	CYD_NoOverlay, // 77
	CYD_EndChannel // 78
};

// message content type declaration
enum CYD_type : uint8_t
{
	CYD_void,
	CYD_string,
	CYD_boolean,
	CYD_byte,
	CYD_int,
	CYD_uint,
	CYD_long,
	CYD_ulong,
	CYD_float,
	CYD_error 
};

// send parameter declaration
enum CYD_param : uint8_t
{
	CYD_NOPARAM,
	CYD_MAXVALUE,
	CYD_VALUECOUNT,
	CYD_ROLLING,
	CYD_STATIC,
	CYD_CLEAR,
	CYD_COLOR,
	CYD_BACKCOLOR,
	CYD_FONT,
	CYD_TITLE
};

// screen identifier
enum CYD_screen : uint8_t
{
	CYD_ALL,
	CYD_HOME,
	CYD_MONITOR,
	CYD_INFO
};

enum CYD_font : uint8_t
{
	CYD_NOFONT0,
	CYD_SMALL,   // font 1
	CYD_NORMAL,  // font 2
	CYD_NOFONT3,
	CYD_BIG      // font 4
};

// color name definition
enum CYD_color : uint8_t
{
	CYD_BLACK,
	CYD_GRAY,
	CYD_PURPLE,
	CYD_PINK,
	CYD_LBLUE,
	CYD_BLUE,
	CYD_DBLUE,
	CYD_GREEN,
	CYD_YELLOW,
	CYD_ORANGE,
	CYD_RED,
	CYD_BROWN,
	CYD_WHITE
};

// Mapping the CYD_Color to the TFT_Color
const uint16_t CYD_TFT_Colors[] = 
{
	TFT_BLACK,
	TFT_LIGHTGREY,
	TFT_PURPLE,
	TFT_PINK,
	TFT_SKYBLUE,
	TFT_BLUE,
	TFT_NAVY,
	TFT_GREEN,
	TFT_YELLOW,
	TFT_ORANGE,
	TFT_RED,
	TFT_BROWN,
	TFT_WHITE
};
	
	
//-----------------------------------------------------------------------------
class UIComponent
{
	public:
		UIComponent(uint16_t x, uint16_t y, uint16_t w, uint16_t h, CYD_channel overlay = CYD_NoOverlay, CYD_screen screen = CYD_HOME ) 
		: _x(x), _y(y), _w(w), _h(h), _overlay(overlay), _screen(screen) {} 
		virtual void CYD_Visible(bool visible);
		virtual void CYD_Font(uint16_t font);
		virtual void CYD_Color(uint16_t color);
		virtual void CYD_BGColor(uint16_t color);
		virtual void CYD_Draw(bool update);
		virtual uint16_t CYD_HandleClick(int x, int y, bool c);
		virtual void CYD_HandleMessage(CYD_param param, CYD_type type);
		virtual ~UIComponent() {} 
	
	protected:	
		uint16_t _x;
		uint16_t _y;
		uint16_t _w;
		uint16_t _h;
		bool _visible = false;
		CYD_channel _overlay;
		
	public:	
		bool _inUse = false;
		CYD_screen _screen;	
};

//-----------------------------------------------------------------------------
class Button : public UIComponent
{
	public:
		using UIComponent::UIComponent;
		void CYD_Color(uint16_t color) override;
		void CYD_BGColor(uint16_t color) override;
		void CYD_Font(uint16_t font) override;
		void CYD_Draw(bool update) override;
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;
	
	private:	
		char _text[BUTTON_TXT_BUFFER_SIZE]="";
		uint16_t _color = TFT_BLACK;
		uint16_t _bgcolor = TFT_LIGHTGREY;
		uint16_t _font = 2;
};

//-----------------------------------------------------------------------------
class Slider : public UIComponent
{
	public:
		Slider(uint16_t x, uint16_t y, uint16_t w, uint16_t h, CYD_channel overlay = CYD_NoOverlay, CYD_screen screen = CYD_HOME);
		void CYD_Color(uint16_t color) override;
		void CYD_BGColor(uint16_t color) override;
		void CYD_Font(uint16_t font) override;
		void CYD_Draw(bool update) override;
		void CYD_Value(uint16_t value);
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;
	
	private:	
		char _text[BUTTON_TXT_BUFFER_SIZE]="";
		int16_t  _scx;
		int16_t  _scy;
		int16_t  _scw;
		int16_t  _sch;
		int16_t  _scxMin;
		int16_t  _scxMax;
		int16_t  _scRange;
		int16_t  _scxOld = 0;
		int16_t  _value = 0;
		int16_t  _maxValue = 100;
		uint16_t _color = TFT_BLACK;
		uint16_t _bgcolor = TFT_LIGHTGREY;
		uint16_t _slidercolor = 0xE73C; // grey lighter than tft_lightgrey
		uint16_t _font = 2;
};

//-----------------------------------------------------------------------------
class Display : public UIComponent
{
	public:
		using UIComponent::UIComponent;
		void CYD_Color(uint16_t color) override;
		void CYD_BGColor(uint16_t color) override;
		void CYD_Font(uint16_t font) override;
		void CYD_Draw(bool update) override;
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;

	private:	
		char _text[DISPLAY_TXT_BUFFER_SIZE]="";
		uint16_t _bgcolor = TFT_BLACK;
		uint16_t _color = TFT_WHITE;
		uint16_t _font = 2;
};

//-----------------------------------------------------------------------------
class Graph : public UIComponent
{
	public:
		using UIComponent::UIComponent;
		void CYD_Color(uint16_t color) override;
		void CYD_BGColor(uint16_t color) override;
		void CYD_Draw(bool update) override;
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;

	private:	
		uint16_t _color = TFT_WHITE;
		uint16_t _bgcolor = TFT_BLACK;
		uint16_t _valueCount = 50;
		uint8_t  _values[MAX_GRAPH_VALUE_COUNT] = {0};
		uint16_t _valueIdx = 0;
		bool     _rolling = true;
};

//-----------------------------------------------------------------------------
class TextPanel : public UIComponent
{
	public:
		using UIComponent::UIComponent;
		void CYD_Color(uint16_t color) override;
		void CYD_Draw(bool update) override;
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;

	private:	
		uint16_t _color = TFT_BLACK;
		const char* _TextLinePtr[12] = {nullptr};
		uint16_t _TextLineIdx = 0;
};

//-----------------------------------------------------------------------------
class Led : public UIComponent
{
	public:
		using UIComponent::UIComponent;
		void CYD_Color(uint16_t color) override;
		void CYD_Draw(bool update) override;
		uint16_t CYD_HandleClick(int x, int y, bool c) override;
		void CYD_HandleMessage(CYD_param param, CYD_type type) override;
	
	private:	
		uint16_t _color = TFT_WHITE;
};


//-----------------------------------------------------------------------------
class CYD_Panel
{
	public:
		using PanelCallbackFunction = void(*)(CYD_channel);

		CYD_Panel(PanelCallbackFunction CallBackPointer);
		void setScreen(CYD_screen screen);
		void begin(CYD_layout layout = CYD_LAYOUT_1);
		void reset(CYD_layout layout = CYD_LAYOUT_1);
		void receive();
		void GetScreenTouch();
		void HandleSend();
		void sendf(CYD_channel channel, const char* message, ...);
		void send(CYD_channel channel, const char* message);
		void send(CYD_channel channel, uint8_t value);
		void send(CYD_channel channel, int16_t value);
		void send(CYD_channel channel, int value);
		void send(CYD_channel channel, int32_t value);
		void send(CYD_channel channel, CYD_param param);
		void send(CYD_channel channel, CYD_param param, CYD_color colorId);
		void send(CYD_channel channel, CYD_param param, CYD_font fontId);
		void send(CYD_channel channel, CYD_param param, int16_t value);
		void send(CYD_channel channel, CYD_param param, int value);
		void send(CYD_channel channel, CYD_param param, int32_t value);
		void send(CYD_channel channel, CYD_param param, const char* message);
		void send(CYD_channel channel, CYD_layout layoutId = CYD_LAYOUT_1);
		void send(CYD_channel channel, bool visible);
		void HeaderLayout();
		void Layout_1();
		void Layout_2();
		void Layout_3();
		void Layout_4();
		void MonitorLayout();
		void InfoLayout();
		
		// All panel objects are instantiated. Will be (re)constructed from the Layouts
		Button O_MButton_1 { 10, 20, 10, 10 };
		Button O_MButton_2 { 10, 20, 10, 10 };
		Button O_MButton_3 { 10, 20, 10, 10 };

    Display O_ApplicationName  { 10, 20, 10, 10};
		
		Display O_DisplayPanel  { 10, 20, 10, 10 };

		Display O_Display_1  { 10, 20, 10, 10 };
		Display O_Display_2  { 10, 20, 10, 10 };
		Display O_Display_3  { 10, 20, 10, 10 };
		Display O_Display_4  { 10, 20, 10, 10 };
		Display O_Display_5  { 10, 20, 10, 10 };
		Display O_Display_6  { 10, 20, 10, 10 };
		Display O_Display_7  { 10, 20, 10, 10 };
		Display O_Display_8  { 10, 20, 10, 10 };
		Display O_Display_9  { 10, 20, 10, 10 };
		Display O_Display_10 { 10, 20, 10, 10 };
		
		Graph O_Graph_1  {10, 20, 10, 10 };
		Graph O_Graph_2  {10, 20, 10, 10 };
		Graph O_Graph_3  {10, 20, 10, 10 };

		Button O_Button_1  { 10, 20, 10, 10 };
		Button O_Button_2  { 10, 20, 10, 10 };
		Button O_Button_3  { 10, 20, 10, 10 };
		Button O_Button_4  { 10, 20, 10, 10 };
		Button O_Button_5  { 10, 20, 10, 10 };
		Button O_Button_6  { 10, 20, 10, 10 };
		Button O_Button_7  { 10, 20, 10, 10 };
		Button O_Button_8  { 10, 20, 10, 10 };
		Button O_Button_9  { 10, 20, 10, 10 };
		Button O_Button_10 { 10, 20, 10, 10 };
		Button O_Button_11 { 10, 20, 10, 10 };
		Button O_Button_12 { 10, 20, 10, 10 };
		Button O_Button_13 { 10, 20, 10, 10 };
		Button O_Button_14 { 10, 20, 10, 10 };
		Button O_Button_15 { 10, 20, 10, 10 };
		Button O_Button_16 { 10, 20, 10, 10 };
		Button O_Button_17 { 10, 20, 10, 10 };
		Button O_Button_18 { 10, 20, 10, 10 };

		Slider O_Slider_1 { 10, 20, 10, 10 };
		Slider O_Slider_2 { 10, 20, 10, 10 };
		Slider O_Slider_3 { 10, 20, 10, 10 };
		Slider O_Slider_4 { 10, 20, 10, 10 };
		Slider O_Slider_5 { 10, 20, 10, 10 };
		Slider O_Slider_6 { 10, 20, 10, 10 };
		Slider O_Slider_7 { 10, 20, 10, 10 };
		Slider O_Slider_8 { 10, 20, 10, 10 };
		Slider O_Slider_9 { 10, 20, 10, 10 };
		
		Led O_Led_1  { 10, 20, 10, 10 };
		Led O_Led_2  { 10, 20, 10, 10 };
		Led O_Led_3  { 10, 20, 10, 10 };
		Led O_Led_4  { 10, 20, 10, 10 };
		Led O_Led_5  { 10, 20, 10, 10 };
		Led O_Led_6  { 10, 20, 10, 10 };
		Led O_Led_7  { 10, 20, 10, 10 };
		Led O_Led_8  { 10, 20, 10, 10 };
		Led O_Led_9  { 10, 20, 10, 10 };
		Led O_Led_10 { 10, 20, 10, 10 };
		Led O_Led_11 { 10, 20, 10, 10 };
		Led O_Led_12 { 10, 20, 10, 10 };

		Led O_Led_13 { 10, 20, 10, 10 };
		Led O_Led_14 { 10, 20, 10, 10 };
		Led O_Led_15 { 10, 20, 10, 10 };
		Led O_Led_16 { 10, 20, 10, 10 };
		Led O_Led_17 { 10, 20, 10, 10 };
		Led O_Led_18 { 10, 20, 10, 10 };
		Led O_Led_19 { 10, 20, 10, 10 };
		Led O_Led_20 { 10, 20, 10, 10 };
		Led O_Led_21 { 10, 20, 10, 10 };
		Led O_Led_22 { 10, 20, 10, 10 };

		Display O_MonitorField_1 { 10, 20, 10, 10 };
		Display O_MonitorField_2 { 10, 20, 10, 10 };
		Display O_MonitorField_3 { 10, 20, 10, 10 };
		Display O_MonitorField_4 { 10, 20, 10, 10 };
		Display O_MonitorField_5 { 10, 20, 10, 10 };
		Display O_MonitorField_6 { 10, 20, 10, 10 };
		
		TextPanel O_InfoPanel{ 10, 20, 10, 10 };

  public:
	  const uint16_t _panelcolor = TFT_DARKGREY;
		
		UIComponent * PanelElements[CYD_EndChannel]; // list of UIComponent Pointers size EndChannel value.
	
// receive vars picked up by Panel.receive() set by panel actions
		CYD_channel cydr_channel = CYD_EndChannel;
		CYD_type  cydr_type = CYD_type::CYD_error;
		bool     cydr_boolean = false;
		char*    cydr_string = nullptr;
		uint8_t  cydr_byte = 0;
		int16_t  cydr_int = 0;
		int32_t  cydr_long = 0;

		volatile bool cydr_received = false;

	
// send vars filled from send(f) functions
		CYD_channel cyds_channel = CYD_EndChannel;
	  CYD_param		cyds_param = CYD_NOPARAM;
		CYD_type    cyds_type = CYD_error;
		bool        cyds_boolean = false;
		const char* cyds_string = nullptr;
	  uint8_t  		cyds_byte = 0;
	  int16_t  		cyds_int = 0;
	  int32_t  		cyds_long = 0;

	  volatile bool	cyds_sent = false; 
		
	private:
		PanelCallbackFunction _CallBackPointer = nullptr;

};

void PanelCallback(CYD_channel event); // Callback Function declaration. Calback routine itself must be created in the sketch

extern CYD_Panel Panel; // Panel object declaration

void Task1code( void * pvParameters );

void WriteText(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, uint16_t font, const char* text, bool center);

extern TFT_eSPI tft;

extern SPIClass touchscreenSPI;

extern XPT2046_Touchscreen touchscreen;