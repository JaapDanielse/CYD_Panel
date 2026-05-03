// Support.cpp - part of CYD_Panel

#include "CYD_Panel.h"

//=====================================================================================
// Support functions for CYD_Panel

//-------------------------------------------------------------------------------------
void WriteText(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, uint16_t font, const char* text, bool center) 
{
	#define MAX_SUBSTRINGS 3 // 
	#define MAX_STRING_LENGHT 60 //
	
	char  substrings[MAX_SUBSTRINGS][MAX_STRING_LENGHT];
	int   substring_count = 0;
	const char *start = text;
	const char *end = text;
	int16_t heigth = 0;
	int16_t width = 0;
	int topmargin = 0;

	char btext[MAX_STRING_LENGHT]="";

	//tft.fillRect(_x, _y, _w, _h, _bgcolor); // x, y, size x, size y color (rectangle)
	tft.setTextColor(color); // text color

	while (*end != '\0' && substring_count < MAX_SUBSTRINGS) 
	{
		if (*end == '\n' || *(end + 1) == '\0') 
		{ // Calculate length of substring
			size_t length = end - start;
			if (*(end + 1) == '\0') length++; // Include the null-terminator if it's the last substring
			// Copy the substring into the appropriate place in the substrings array
			strncpy(substrings[substring_count], start, length);
			substrings[substring_count][length] = '\0';  // Null-terminate the substring
			substring_count++;
			start = end + 1;  // Move to the next substring after '\n'
		}
	end++;
	}

	heigth = tft.fontHeight(font);

	for(int i=substring_count; i>0; i--)
	{
		if((heigth * i) < h)
		{
			substring_count = i;
			break;
		}
	}

	topmargin = ((h - ((heigth + 1) * substring_count)) / 2) + 1;

	strcpy(btext, text);

	for (int j=0; j < substring_count; j++ )
	{
		for (int i=strlen(substrings[j]); i>0; i--)
		{
			width = tft.textWidth(substrings[j], font);
			if(width <= w-2) 
			{
				if(center)
					tft.drawString(substrings[j], x+((w-width)/2), y + topmargin + (j * (heigth + 1)), font); // text, x, y ,font
				else
					tft.drawString(substrings[j], x+((w-width)), y + topmargin + (j * (heigth + 1)), font); // text, x, y ,font
				break;
			}
			substrings[j][i-1] = 0;
		}
	}
}

