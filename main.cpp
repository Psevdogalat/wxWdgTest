#include <wx/wx.h>

class MainFrame : public wxFrame
{
	public:
		MainFrame();		

		void OnEvent(wxCommandEvent& event);
		void OnExit	(wxCommandEvent& event);
};

class App : public wxApp
{
	private:
		MainFrame * mainFrame;

	public:
		virtual bool OnInit();
		virtual int	 OnExit(); 
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

int App::OnExit()
{
	//mainFrame->Close();
	//delete mainFrame;
	return 0;
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

	Bind(wxEVT_MENU, &MainFrame::OnEvent, this, ID_Event);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}

void MainFrame::OnEvent(wxCommandEvent& WXUNUSED(event))
{
	printf("ouppss!\n");
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}


