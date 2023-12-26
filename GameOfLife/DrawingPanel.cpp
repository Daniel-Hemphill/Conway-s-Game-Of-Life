#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_UP(DrawingPanel::OnClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gReference, std::vector<std::vector<int>>& cReference) : wxPanel(parent, wxID_ANY, wxPoint(0, 0) = wxDefaultPosition, wxSize(size) = wxDefaultSize), gridReference(gReference), countReference(cReference)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}
DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::OnPaint(wxPaintEvent& paint)
{
	wxSize windowSize = this->GetSize();

	int cellWidth = windowSize.x / (float)gameSet->gridSize;
	int cellHeight = windowSize.y / (float)gameSet->gridSize;

	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);

	if(!context)
	{
		return;
	}

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);
	context->SetFont(wxFontInfo(8), *wxRED);
	
	double cellTxtWidth, cellTxtHeight;
	
	for (int i = 0; i < gameSet->gridSize; i++)
	{
		for (int j = 0; j < gameSet->gridSize; j++)
		{
			if (gridReference[j][i])
			{
				context->SetBrush(gameSet->getColor());
			}
			else
			{
				context->SetBrush(*wxWHITE);
			}

			context->DrawRectangle(cellWidth * j, cellHeight * i, cellWidth, cellHeight);

			if (countReference[j][i] > 0)
			{
				wxString cellText = std::to_string(countReference[j][i]);
				context->GetTextExtent(cellText, &cellTxtWidth, &cellTxtHeight);
				context->DrawText(cellText, (cellWidth * j) + cellWidth / 2 - cellTxtWidth / 2, (cellHeight * i) + cellHeight / 2 - cellTxtHeight / 2);
			}
		}
	}
}

void DrawingPanel::SetPanelSize(wxSize& windowSize)
{
	this -> SetSize(windowSize);
	Refresh();
}

void DrawingPanel::SetGridSize(int newGridSize)
{
	gameSet -> gridSize = newGridSize;
}

void DrawingPanel::OnClick(wxMouseEvent& evt)
{
	wxSize windowSize = this->GetSize();
	int x = evt.GetX();
	int y = evt.GetY();
	int cellWidth = windowSize.x / gameSet->gridSize;
	int cellHeight = windowSize.y / gameSet->gridSize;

	boxX = x / cellWidth;
	boxY = y / cellHeight;
	
	if (boxX >= gameSet->gridSize || boxY >= gameSet->gridSize)
	{
		return;
	}

	if(gridReference[boxX][boxY] == false)
	{
		gridReference[boxX][boxY] = true;
	}
	else
	{
		gridReference[boxX][boxY] = false;
	}
	Refresh();
}

void DrawingPanel::SetGameSettings(GameSettings* settings)
{
	gameSet = settings;
}