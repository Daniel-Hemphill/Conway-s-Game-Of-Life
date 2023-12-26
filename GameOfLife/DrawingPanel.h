#pragma once
#include "wx/wx.h"
#include "GameSettings.h"

class DrawingPanel : public wxPanel
{
private:
	int boxX;
	int boxY;
	int gridSize;
	std::vector<std::vector<bool>>& gridReference;
	std::vector<std::vector<int>>& countReference;
public:
	DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gReference, std::vector<std::vector<int>>& cReference);
	~DrawingPanel();

	void OnPaint(wxPaintEvent& paint);
	void SetPanelSize(wxSize& windowSize);
	void OnClick(wxMouseEvent& evt);
	void SetGridSize(int newGridSize);
	void SetGameSettings(GameSettings* settings);

	GameSettings* gameSet;

	wxDECLARE_EVENT_TABLE();
};

