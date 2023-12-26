#pragma once
#include "wx/wx.h"
#include <fstream>

struct GameSettings
{
	int red = 128;
	int blue = 128;
	int green = 128;
	int Alpha = 255;

	int gridSize = 15;

	int interval = 50;

	bool isFinite = true;

	bool ShowNeighborCount = true;

	void setColor(wxColor cellColor)
	{
		red = cellColor.GetRed();
		green = cellColor.GetGreen();
		blue = cellColor.GetBlue();
		Alpha = cellColor.GetAlpha();
	}

	wxColor getColor()
	{
		wxColor cellColor(red, green, blue, Alpha);
		return cellColor;
	}

	void Saving()
	{
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(GameSettings));
		file.close();
	}

	void Loading()
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(GameSettings));
		file.close();
	}

};
