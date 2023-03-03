#include <wx/wx.h>
#include <wx/activityindicator.h>

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
		wxControl * testControl;
		wxButton * enButton;
		wxButton * disButton;	
		wxActivityIndicator * activityIndicator;

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

enum ControlType
{
	CT_Button = 0,
	CT_StaticText,
	CT_CheckBox,
	CT_ListBox,
	CT_CheckListBox,
	CT_Choice
};

const char* ControlTypeStrings[] =
{
	"Button",
	"StaticText",
	"CheckBox",
	"ListBox",
	"CheckListBox",
	"Choice"
};

const wxSize defaultControlSize = wxSize(200, 150);

struct _controlTableRecord{
	const char*  name;
	const char*  caption;
	wxWindowID	 id;
	ControlType  controlType;
	wxSize		 size;
}controlsTable[] = 
{
	{"button",		"btn1",		0, CT_Button, 		defaultControlSize},
	{"static",		"static1",	0, CT_StaticText,	defaultControlSize},
	{"checkbox",	"chk1",		0, CT_CheckBox,		defaultControlSize},
	{"listbox",		"lsb1",		0, CT_ListBox,		defaultControlSize},
	{"CListBox",	"clsb1",	0, CT_CheckListBox,	defaultControlSize},
	{"Choice",		"choice1",	0, CT_Choice,		defaultControlSize}
};


wxControl * createControl(
	wxWindow * 	parent, 
	wxWindowID 	id, 
	wxPoint		position,
	_controlTableRecord& record
){
	wxControl * control;
	
	static const wxString items[]=
	{
		wxString("Item1"), wxString("Item2"), wxString("Item3")
	};

	switch(record.controlType)
		{
			case CT_Button:
				control = new wxButton(parent, id, 
					wxString(record.caption), position, record.size
				);
			
			break;	
			case CT_StaticText:
				control = new wxStaticText(parent, id, 
					wxString(record.caption), position, record.size
				);
			case CT_CheckBox:
				control = new wxCheckBox(parent, id, 
					wxString(record.caption), position, record.size
				);

			break;
			case CT_ListBox:
				control = new wxListBox(parent, id, 
					position, record.size
				);
				
				((wxListBox*)control)->InsertItems(3, items, 0);

			break;
			case CT_CheckListBox:
				control = new wxCheckListBox(parent, id, 
					position, record.size
				);

				((wxCheckListBox*)control)->InsertItems(3, items, 0);

			break;
			case CT_Choice:
				control = new wxChoice(parent, id, 
					position, record.size
				);

				((wxChoice*)control)->Insert(3, items, 0);


			break;
			default:
				printf("undefine type\n");
				return nullptr;	
		}

	return control;
}

wxControl ** controlsMass;
unsigned int controlsNum;

MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, "wxWdgTest", wxDefaultPosition, 
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
		new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize, wxVSCROLL);

	
	controlsNum = sizeof(controlsTable)/sizeof(_controlTableRecord);
	controlsMass = new wxControl* [controlsNum];

	_controlTableRecord* tableRecord = NULL;
	wxControl *		control;
	wxWindowID		controlId;
	wxPoint 		controlPosition;
	wxStaticText *	caption;
	
	controlPosition = wxPoint(150, 10);

	for(unsigned int i = 0; i < controlsNum; i++)
	{
		tableRecord = &controlsTable[i];
		controlId 	= i + 3;
		
		control = createControl(parent, controlId, 
			controlPosition, *tableRecord);
			
		if(!control)
			break;

		(i%2 == 0)?
			control->SetBackgroundColour(*wxWHITE):
			control->SetBackgroundColour(*wxCYAN);
		
		caption = 
			new wxStaticText(parent, wxID_ANY, 
			wxString(tableRecord->name), 
			wxPoint(10, controlPosition.y + tableRecord->size.y/2 - 15),
			wxSize(90, 30));

		controlPosition += wxSize(0, tableRecord->size.y);
	}
	
	parent->SetVirtualSize(wxSize(350, controlPosition.y));
	((wxScrolledWindow*)parent)->SetScrollRate(0, 10);

}

MainFrame::~MainFrame()
{
	printf("main frame destroy \n");
	delete [] controlsMass;	
}

void MainFrame::OnEvent(wxCommandEvent& WXUNUSED(event))
{
	printf("ouppss!\n");
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	printf("MainFrameClose\n");
	Close(true);
}

void MainFrame::OnButton(wxCommandEvent& event)
{
	switch(event.GetId())
	{
		case ID_EnButton:
			enButton->Disable();
			disButton->Enable();
			testControl->Enable();						
			activityIndicator->Start();

		break;
		case ID_DisButton:
			enButton->Enable();
			disButton->Disable();			
			testControl->Disable();
			activityIndicator->Stop();

		break;
		default:
			printf("any button click\n");
	}	

}

void MainFrame::OnControlCommand(wxCommandEvent& event)
{

}

void MainFrame::OnResize(wxSizeEvent& event)
{

	printf("resize\n");
}


