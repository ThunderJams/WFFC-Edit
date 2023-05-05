#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_BUTTON40005, &MFCMain::ToolBarButton2)
	ON_COMMAND(ID_BUTTON40007, &MFCMain::ToolBarButton3)
	ON_COMMAND(ID_BUTTON40009, &MFCMain::ToolBarButton4)
	ON_COMMAND(ID_BUTTON40011, &MFCMain::ToolBarButton5)
	ON_COMMAND(ID_BUTTON40012, &MFCMain::ToolBarButtonRed)
	ON_COMMAND(ID_BUTTON40013, &MFCMain::ToolBarButtonGreen)
	ON_COMMAND(ID_BUTTON40014, &MFCMain::ToolBarButtonBlue)
	
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			std::wstring toolString = L" - Current Tool: " + std::to_wstring(ID);
			if (m_ToolSystem.GetToolMode() == 0) {
				toolString = L" | Tool: Mouse Pick";
			}
			if (m_ToolSystem.GetToolMode() == 1) {
				toolString = L" | Tool: Place Object";
			}
			if (m_ToolSystem.GetToolMode() == 2) {
				toolString = L" | Tool: Edit Terrain";
			}

			std::wstring terrainInfoString = L" ";
			if (m_ToolSystem.GetTerrainIntersect().x != 99999) terrainInfoString = L" | Terrain Point Co-ords: " + std::to_wstring((int)m_ToolSystem.GetTerrainIntersect().x) + L", " + std::to_wstring((int)m_ToolSystem.GetTerrainIntersect().y) + L", " + std::to_wstring((int)m_ToolSystem.GetTerrainIntersect().z);
			
			

			std::wstring statusStringFinal = statusString + toolString + terrainInfoString;
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusStringFinal.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

void MFCMain::ToolBarButton2()
{

	m_ToolSystem.SetObjectSpawning(false);
}

void MFCMain::ToolBarButton3()
{

	m_ToolSystem.SetObjectSpawning(true);
}

void MFCMain::ToolBarButton4()
{

	m_ToolSystem.Wireframe(!m_ToolSystem.GetWireframe());

}

void MFCMain::ToolBarButton5()
{

	m_ToolSystem.SetTerrainEdit(!m_ToolSystem.GetTerrainEdit());

}

void MFCMain::ToolBarButtonRed()
{

	m_ToolSystem.UpdateColours(true, false, false);

}

void MFCMain::ToolBarButtonGreen()
{

	m_ToolSystem.UpdateColours(false, true, false);

}

void MFCMain::ToolBarButtonBlue()
{

	m_ToolSystem.UpdateColours(false, false, true);

}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
