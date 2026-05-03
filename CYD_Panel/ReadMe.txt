CYD_Panel Release 1.0.0 (May 2026)

CYD_Panel is an Arduino libray to implement a simple UI tool for experiment and prototyping on the Cheap Yellow display.

Cheap Yellow Display (CYD)
  The Cheap Yellow Display is a specific module based on the ESP32 wroom, 320 x 240 TFT display and a Touch screen.
  The library is specific to this module.
  The library runs (mainly) on Core 0 the user code on Core 1

Required underlying libraries
  CYD_Panel is built on top of the TFT_eSPI library by Bodmer: https://github.com/Bodmer/TFT_eSPI,
  and the XPT2046_Touchscreen library by Paul Stoffregen: https://github.com/PaulStoffregen/XPT2046_Touchscreen.
  See instructions on  https://github.com/JaapDanielse/CYD_Panel/wiki/Getting-Started.
	
Installing the CYD_Panel library
  CYD_Panel can be installed as a standard Arduino .zip library.
  . In the Arduino IDE select: Sketch->Include Library->Add .ZIP Library...
  . Select CYD_Panel.zip from your download location.
  See instructions on  https://github.com/JaapDanielse/CYD_Panel/wiki/Getting-Started.

Examples
  See examples in: myDocuments\Arduino\libraries\CYD_Panel\examples

Extras
  See Quick reference in: myDocuments\Arduino\libraries\CYD_Panel\extras


CYD_Panel V1.0.0 was built and tested using Arduino 2.3.6 IDE
