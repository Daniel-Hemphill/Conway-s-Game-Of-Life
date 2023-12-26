#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(15, SettingsDialog::Spin)
EVT_SPINCTRL(25, SettingsDialog::GridSizeChange)
EVT_COLOURPICKER_CHANGED(20, SettingsDialog::ColourPick)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Settings", wxPoint(100, 100), wxSize(200, 200))
{
	wxBoxSizer* boxV = new wxBoxSizer(wxVERTICAL);
	SetSizer(boxV);

	wxBoxSizer* boxS = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lbleSpin = new wxStaticText(this, wxID_ANY, "Interval");
	wxStaticText* gridSpin = new wxStaticText(this, 25, "Grid Size");
	boxS->Add(lbleSpin);
	boxS->Add(spinID);

	boxS->Add(gridSpin);
	boxS->Add(gridChange);

	wxBoxSizer* boxC = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lblePicker = new wxStaticText(this, wxID_ANY, "Colour Picker");
	boxC->Add(lblePicker);
	boxC->Add(cPicker);

	boxV->Add(boxS);
	boxV->Add(boxC);

	wxSizer* ok = CreateButtonSizer(wxOK | wxCANCEL);

	boxV->Add(ok);
}

void SettingsDialog::Spin(wxSpinEvent& evt)
{
	gameSet->interval = evt.GetInt();
}
void SettingsDialog::ColourPick(wxColourPickerEvent& evt)
{
	gameSet->setColor(evt.GetColour());
}
void SettingsDialog::GridSizeChange(wxSpinEvent& evt)
{
	gameSet->gridSize = evt.GetInt();
}