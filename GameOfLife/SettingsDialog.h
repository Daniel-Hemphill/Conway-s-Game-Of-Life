#pragma once
#include "GameSettings.h"
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"

class SettingsDialog : public wxDialog
{
private:
	wxColourPickerCtrl* cPicker = new wxColourPickerCtrl(this, 20);
	wxSpinCtrl* spinID = new wxSpinCtrl(this, 15);
	wxSpinCtrl* gridChange = new wxSpinCtrl(this, 25);
	wxCheckBox* nC = new wxCheckBox();
public:
	SettingsDialog(wxWindow* parent);

	GameSettings* gameSet;

	void Spin(wxSpinEvent& evt);
	void GridSizeChange(wxSpinEvent& evt);
	void ColourPick(wxColourPickerEvent& evt);

	wxDECLARE_EVENT_TABLE();

	
};

