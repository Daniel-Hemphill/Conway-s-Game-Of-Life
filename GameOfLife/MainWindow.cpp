#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10000, MainWindow::OnPlayClick)
EVT_MENU(10001, MainWindow::OnPauseClick)
EVT_MENU(10002, MainWindow::OnNextClick)
EVT_MENU(10003, MainWindow::OnTrashClick)
EVT_TIMER(10004, MainWindow::Timer)
EVT_MENU(10005, MainWindow::Settings)
EVT_MENU(10006, MainWindow::PopulateMatrix)
EVT_MENU(wxID_NEW, MainWindow::NewFile)
EVT_MENU(wxID_OPEN, MainWindow::Open)
EVT_MENU(wxID_SAVE, MainWindow::Save)
EVT_MENU(wxID_SAVEAS, MainWindow::SaveAs)
EVT_MENU(10009, MainWindow::ResetSettings)
EVT_MENU(10010, MainWindow::OnClickImport)
EVT_MENU(10011, MainWindow::Exit)
EVT_MENU(10012, MainWindow::OnFianiteClick)
EVT_MENU(10013, MainWindow::OnTorodialClick)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0,0) = wxDefaultPosition, wxSize(200,200) = wxDefaultSize)
{
	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);

	gameSet.Loading();
	wxMenuBar* mBar = new wxMenuBar();
	this->SetMenuBar(mBar);

	wxMenu* settings = new wxMenu();
	settings->Append(10005, "Settings");
	settings->Append(10009, "Reset Settings");

	wxMenu* rnd = new wxMenu();
	rnd->Append(10006, "Random Board");

	wxMenu* file = new wxMenu();
	file->Append(wxID_NEW);
	file->Append(wxID_OPEN);
	file->Append(wxID_SAVE);
	file->Append(wxID_SAVEAS);
	file->Append(10010, "Import");
	file->Append(10011, "Exit");
	
	wxMenu* viewMenu = new wxMenu();
	universeFinite = new wxMenuItem(viewMenu, 10012, "Finite", "", wxITEM_CHECK);
	universeFinite->SetCheckable(true);
	viewMenu->Append(universeFinite);

	universeTorodial = new wxMenuItem(viewMenu, 10013, "Toroidal", "", wxITEM_CHECK);
	universeTorodial->SetCheckable(true);
	viewMenu->Append(universeTorodial);
	

	mBar->Append(file, "File");
	mBar->Append(viewMenu, "View");
	mBar->Append(settings, "Settings");
	mBar->Append(rnd, "Random");


	statusBar = CreateStatusBar();
	StatusUpdate();

	toolBar = CreateToolBar();
	toolBar->AddTool(10000, "Play", playIcon);
	toolBar->AddTool(10001, "Pause", pauseIcon);
	toolBar->AddTool(10002, "Next", nextIcon);
	toolBar->AddTool(10003, "Trash", trashIcon);
	toolBar->Realize();

	timer = new wxTimer(this, 10004);
	panel = new DrawingPanel(this, wxSize(100, 100), gameBoard, neighCount);
	sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(panel, 1, wxEXPAND|wxALL);
	this->SetSizer(sizer);

	panel->SetGameSettings(&gameSet);

	Grid();

	this->Layout();
	RefreshMenuItems();
}

MainWindow::~MainWindow()
{

}

void MainWindow::Grid()
{
	gameBoard.resize(gameSet.gridSize);
	sandbox.resize(gameSet.gridSize);
	neighCount.resize(gameSet.gridSize);
	panel->SetGridSize(gameSet.gridSize);

	for (int i = 0; i < gameSet.gridSize; i++)
	{
			gameBoard[i].resize(gameSet.gridSize);
			sandbox[i].resize(gameSet.gridSize);
			neighCount[i].resize(gameSet.gridSize);
	}
}

int MainWindow::NeighborCount(int row, int column)
{
	int count = 0;
	int gridSize = gameBoard.size();

	for (int i = row - 1; i <= row + 1; i++)
	{
		for (int j = column - 1; j <= column + 1; j++)
		{
			int tempI = i;
			int tempJ = j;

			if (!gameSet.isFinite)
			{
				if (i < 0)
				{
					tempI = gridSize - 1;
				}
				else if (i >= gridSize)
				{
					tempI = 0;
				}

				if (j < 0)
				{
					tempJ = gridSize - 1;
				}
				else if (j >= gridSize)
				{
					tempJ = 0;
				}
			}
			else
			{
				if (i >= gridSize || j >= gridSize || i < 0 || j < 0)
				{
					continue;
				}
			}

			if (tempI == row && tempJ == column)
			{
				continue;
			}

			if (gameBoard[tempI][tempJ] == true)
			{
				count++;
			}
		}
	}
	return count;
}
void MainWindow::Generations()
{
	sandbox = gameBoard;
	livingCells = 0;
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < gameBoard.size(); j++)
		{
			int nCount = NeighborCount(i, j);
			bool cell = gameBoard[i][j];
			if((nCount < 2 || nCount > 3) && cell == true)
			{
				livingCells--;
				sandbox[i][j] = false;
				
			}
			else if(nCount == 3 &&  cell == false)
			{
				livingCells++;
				sandbox[i][j] = true;
				
			}
			if (cell == true)
			{
				livingCells++;
			}
		}
	}
	sandbox.swap(gameBoard);
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < gameBoard.size(); j++)
		{
			int nCount = NeighborCount(i, j);
			neighCount[i][j] = nCount;
		}
	}
	generation++;
	StatusUpdate();
	panel->Refresh();
}
void MainWindow::OnSizeChange(wxSizeEvent& evt)
{
	wxSize windowSize = evt.GetSize();
	if (panel == nullptr)
	{
		return;
	}
	panel->SetPanelSize(windowSize);
	evt.Skip();
}
void MainWindow::StatusUpdate()
{
	wxString format = wxString::Format("Generations: %d Living Cells: %d", generation, livingCells);
	statusBar->SetStatusText(format);
}

void MainWindow::OnPlayClick(wxCommandEvent& evt)
{
	timer->Start(time);
}
void MainWindow::OnPauseClick(wxCommandEvent& evt)
{
	timer->Stop();
}
void MainWindow::OnNextClick(wxCommandEvent& evt)
{
	Generations();
}
void MainWindow::OnTrashClick(wxCommandEvent& evt)
{
	generation = 0;
	livingCells = 0;
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < gameBoard.size(); j++)
		{
			gameBoard[i][j] = false;
			neighCount[i][j] = 0;
		}
	}
	
	StatusUpdate();
	timer->Stop();
	panel->Refresh();
}

void MainWindow::Timer(wxTimerEvent& evt)
{
	Generations();
}
void MainWindow::NewFile(wxCommandEvent& evt)
{
	
}
void MainWindow::Open(wxCommandEvent& evt)
{
	wxFileDialog fileDialog(this, "Open Game of Life File", "", "", "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	for (int i = 0; i < gameBoard.size(); i++)
	{
		gameBoard[i].clear();
		gameBoard.resize(0);
	}
	gameBoard.clear();
	gameBoard.resize(0);

	std::string buffer;
	std::ifstream fileStream;
	int index = 0;

	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open())
	{

		while (!fileStream.eof())
		{
			std::getline(fileStream, buffer);

			if (buffer.size() == 0){break;}

			if (gameBoard.size() == 0)
			{
				gameBoard.resize(buffer.size());
			}

			gameBoard[index].resize(buffer.size());
			for (int i = 0; i < buffer.size(); i++)
			{
				if (buffer[i] == '*')
				{
					gameBoard[index][i] = true;
				}
				else
				{
					gameBoard[index][i] = false;
				}

			}
			index++;
		}

		fileStream.close();
	}

	panel->Refresh();
	evt.Skip();
}
void MainWindow::Save(wxCommandEvent& evt)
{
	wxFileDialog fileDialog(this, "Save Game of Life File", "", "", "Game of Life Files (*.cells) | *.cells", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	std::ofstream fileStream;

	fileStream.open((std::string)fileDialog.GetPath());
	if (fileStream.is_open())
	{
		for (int i = 0; i < gameBoard.size(); i++)
		{
			for (int j = 0; j < gameBoard.size(); j++)
			{
				if (gameBoard[i][j] == true)
				{
					fileStream << '*';
				}
				else
				{
					fileStream << '.';
				}
			}
			fileStream << '\n';
		}

		fileStream.close();
	}
	evt.Skip();
}
void MainWindow::SaveAs(wxCommandEvent& evt)
{
	wxFileDialog fileDialog(this, "Save Game of Life File", "", "", "Game of Life Files (*.cells) | *.cells", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	std::ofstream fileStream;

	fileStream.open((std::string)fileDialog.GetPath());
	if (fileStream.is_open())
	{
		for (int i = 0; i < gameBoard.size(); i++)
		{
			for (int j = 0; j < gameBoard.size(); j++)
			{
				if (gameBoard[i][j] == true)
				{
					fileStream << '*';
				}
				else
				{
					fileStream << '.';
				}
			}
			fileStream << '\n';
		}

		fileStream.close();
	}
	evt.Skip();
}
void MainWindow::Exit(wxCommandEvent& evt)
{
	exit(0);
}
void MainWindow::OnClickImport(wxCommandEvent& evt)
{
	wxFileDialog fileDialog(this, "Open Game of Life File", "", "", "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	std::string buffer;
	std::ifstream fileStream;
	int index = 0;

	fileStream.open((std::string)fileDialog.GetPath());

	if (fileStream.is_open())
	{

		while (!fileStream.eof())
		{
			std::getline(fileStream, buffer);

			if (buffer.size() == 0) { break; }

			for (int i = 0; i < buffer.size(); i++)
			{
				if (buffer[i] == '*')
				{
					gameBoard[index][i] = true;
				}
				else
				{
					gameBoard[index][i] = false;
				}

			}
			index++;
		}
		fileStream.close();
	}

	panel->Refresh();
	evt.Skip();
}
void MainWindow::Settings(wxCommandEvent& evt)
{
	SettingsDialog* diag = new SettingsDialog(this);
	diag -> gameSet = &gameSet;
	if (diag->ShowModal() == wxID_OK)
	{
		Grid();
		panel->Refresh();
		gameSet.Saving();
	}
}
void MainWindow::ResetSettings(wxCommandEvent& evt)
{
	gameSet.interval = 15;
	gameSet.gridSize = 15;
	wxColor cellColor(128, 128, 128, 255);
	gameSet.setColor(cellColor);
	gameSet.Saving();

	panel->Refresh();

}
void MainWindow::PopulateMatrix(wxCommandEvent& evt)
{
	srand(std::time(NULL));
	
	for (int i = 0; i < gameBoard.size(); i++)
	{
		for (int j = 0; j < gameBoard[i].size(); j++)
		{
			int num = rand();
			if (num % 100 < 45)
			{
				gameBoard[i][j] = true;
			}
			else
			{
				gameBoard[i][j] = false;
			}
		}
	}
	panel->Refresh();
}
void MainWindow::OnTorodialClick(wxCommandEvent& evt)
{
	gameSet.isFinite = false;
	RefreshMenuItems();
	evt.Skip();
}
void MainWindow::OnFianiteClick(wxCommandEvent& evt)
{
	gameSet.isFinite = true;
	RefreshMenuItems();
	evt.Skip();
}
void MainWindow::RefreshMenuItems()
{
	universeFinite->Check(gameSet.isFinite);
	universeTorodial->Check(!gameSet.isFinite);
	gameSet.Saving();
}