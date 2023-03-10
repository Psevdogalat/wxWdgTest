#include <wx/wx.h>
#include <wx/activityindicator.h>


const char* appName = "sizeers test";

class MainFrame : public wxFrame
{
	public:
		MainFrame();		
		~MainFrame();		

		void OnEvent	(wxCommandEvent& );
		void OnExit		(wxCommandEvent& );
		void OnButton	(wxCommandEvent& );
		void OnResize	(wxSizeEvent& );
		void OnControlCommand(wxCommandEvent& );
	private:
		wxControl 	* testControl;
		wxButton 	* enButton;
		wxButton 	* disButton;	
		wxActivityIndicator * activityIndicator;
		
		wxStatusBar * statusBar;
		wxListBox	* listBox;
		wxTextCtrl	* logBox;
		wxListBox	* propBox;
		wxTextCtrl	* cmdBox;

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
	ID_Event = 1,
	ID_EnButton,
	ID_DisButton
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
	printf("app OnExit\n");
	//mainFrame->Close();
	//delete mainFrame;
	return 0;
}


MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, appName, wxDefaultPosition, 
		wxSize(500, 700))
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

	wxWindow * parent = 
		new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	listBox = 
	new wxListBox(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	
	propBox = 
	new wxListBox(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 300));

	cmdBox =
	new wxTextCtrl(parent, wxID_ANY, wxEmptyString, 
		wxDefaultPosition, wxSize(400, -1));
	
	logBox =
	new wxTextCtrl(parent, wxID_ANY, wxEmptyString, 
		wxDefaultPosition, wxSize(600, 200), 
		wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

	statusBar = new wxStatusBar(this, wxID_ANY);

	wxString items[]=
	{
		wxString("Item1"),
		wxString("Item2"),
		wxString("Item3")
	};

	listBox->Append(3, items);
	propBox->Append(3, items);

	wxBoxSizer * sizer0 = new wxBoxSizer( wxVERTICAL);
	sizer0->Add(listBox, 1, wxEXPAND);
	sizer0->Add(cmdBox,  0, wxEXPAND | wxNORTH, 10);
	
	wxBoxSizer * sizer1 = new wxBoxSizer(wxHORIZONTAL);
	sizer1->Add(sizer0,  1, wxEXPAND | wxALL, 5);
	sizer1->Add(propBox, 0, wxEXPAND | wxALL, 5);
	
	wxBoxSizer * sizer2 = new wxBoxSizer( wxVERTICAL);
	sizer2->Add(sizer1, 1, wxEXPAND);
	sizer2->Add(logBox, 0, wxEXPAND | wxALL, 5);	
	
	parent->SetSizerAndFit(sizer2);
	parent->Layout();	

	SetStatusBar(statusBar);
	SetMinSize(wxSize(640, 420));
	
}

MainFrame::~MainFrame()
{
	printf("main frame destroy \n");
}

void MainFrame::OnEvent(wxCommandEvent& WXUNUSED(event))
{
	printf("OnEvent\n");
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	printf("OnExit\n");
	Close(true);
}

void MainFrame::OnButton(wxCommandEvent& event)
{
	printf("OnButton\n");
}

void MainFrame::OnControlCommand(wxCommandEvent& event)
{
	printf("OnControlCommand\n");
}

void MainFrame::OnResize(wxSizeEvent& event)
{
	printf("OnResize\n");
}


