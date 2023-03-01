#include <wx/wx.h>

class MainFrame : public wxFrame
{
	public:
		MainFrame();		

		void onEvent(wxCommandEvent& event);
		void onExit	(wxCommandEvent& event);
};

class App : public wxApp
{
	private:
		MainFrame * mainFrame;

	public:
		virtual bool OnInit();
};


enum
{
	ID_Event = 1
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	mainFrame = new MainFrame();
	mainFrame->Show(true);
	return true;
}

MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, "Hello world")
{
	wxMenu * menuFile = new wxMenu();
	menuFile->Append(ID_Event, "&Hello event...\tCtrl-H",
		"Help string for hello event menu");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenuBar * menuBar = new wxMenuBar();
	menuBar->Append(menuFile, "file");

	SetMenuBar( menuBar);

	Bind(wxEVT_MENU, &MainFrame::onEvent, this, ID_Event);
	Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);
}

void MainFrame::onEvent(wxCommandEvent& event)
{
	printf("ouppss!\n");
}

void MainFrame::onExit(wxCommandEvent& event)
{
	Close(true);
}


