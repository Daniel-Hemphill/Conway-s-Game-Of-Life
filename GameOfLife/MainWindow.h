#pragma once
#include "wx/wx.h"
#include "wx/filedlg.h"
#include "DrawingPanel.h"
#include "GameSettings.h"
#include "SettingsDialog.h"
#include "play.xpm"
#include "trash.xpm"
#include "pause.xpm"
#include "next.xpm"

class MainWindow : public wxFrame
{
private:
	int generation;
	int livingCells;
	wxStatusBar* statusBar;
	

public:
	MainWindow();
	~MainWindow();

	// Event Handlers
	void OnSizeChange(wxSizeEvent& evt);
	void OnPlayClick(wxCommandEvent& evt);
	void OnPauseClick(wxCommandEvent& evt);
	void OnNextClick(wxCommandEvent& evt);
	void OnTrashClick(wxCommandEvent& evt);
	void Timer(wxTimerEvent& evt);
	void NewFile(wxCommandEvent& evt);
	void Open(wxCommandEvent& evt);
	void Save(wxCommandEvent& evt);
	void SaveAs(wxCommandEvent& evt);
	void OnClickImport(wxCommandEvent& evt);
	void Exit(wxCommandEvent& evt);
	void Settings(wxCommandEvent& evt);
	void ResetSettings(wxCommandEvent& evt);
	void PopulateMatrix(wxCommandEvent& evt);
	void OnFianiteClick(wxCommandEvent& evt);
	void OnTorodialClick(wxCommandEvent& evt);

	// Logic 
	void Grid();
	void StatusUpdate();
	void Generations();
	void setColor(wxColor cellColor);
	void RefreshMenuItems();
	
	int NeighborCount(int row, int column);
	
	GameSettings gameSet{};

	int time = gameSet.interval;
	DrawingPanel* panel;
	wxBoxSizer* sizer = nullptr;
	wxMenuItem* universeFinite = nullptr;
	wxMenuItem* universeTorodial = nullptr;
	std::vector<std::vector<bool>> gameBoard;
	std::vector<std::vector<bool>> sandbox;
	std::vector<std::vector<int>> neighCount;

	wxToolBar* toolBar;
	wxTimer* timer;

	wxDECLARE_EVENT_TABLE();
};