// PCMan4.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PCMan.h"

#include "MainFrm.h"

#include <wininet.h>
#include "WinUtils.h"

#include "SearchPlugin.h"
#include "OleImage.h"
#include "Minidump.h"

/* On some computer, Visual Style will not be enabled without this.  */
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef	_COMBO_
//	#include <..\src\occimpl.h>
#include "..\Combo\CustSite.h"
#include "..\Combo\Version.h"
#else
#include "..\Lite\Version.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef	_COMBO_
#include "..\Combo\WebManagerIE.h"
#include "..\Combo\WebManagerCEF.h"

WebManager *g_webmanager;
#endif

CString AppPath;
CString ConfigPath;
CString DefaultConfigPath;

/////////////////////////////////////////////////////////////////////////////
// CApp

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	//{{AFX_MSG_MAP(CApp)
	ON_COMMAND(ID_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApp construction

CApp::CApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CApp object

CApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CApp initialization

BOOL CApp::InitInstance()
{
#if defined (_COMBO_)
	//g_webmanager = new WebManagerIE();
	g_webmanager = new WebManagerCEF();
	if (g_webmanager->OnAppStart(m_hInstance) >= 0)
	{
		return FALSE;
	}
#endif
	// In newer Windows SDK, LoadString() uses CP_THREAD_ACP for converting string,
	// i.e., first argument of WideCharToMultiByte(). On some non-Chinese version Windows,
	// e.g., English version with Chinese locale, thread-locale is by default 1033 (English)
	// instead of user locale 1028 (Chinese). I'm not sure why.
	// To workaround this issue, either we change the thread locale to user locale,
	// or use CP_ACP instead of CP_THREAD_ACP (defining _CONVERSION_DONT_USE_THREAD_LOCALE)
	// for converting string. See the following functions/macros for details
	// LoadString() -> StringTraits::ConvertToBaseType() -> _AtlGetConversionACP()
	// CP_ACP/CP_THREAD_ACP
	SetThreadLocale(GetUserDefaultLCID());

	Minidump::RegisterHandler();

	DBG_INIT(1);

	// Find other existing instances
	HWND mainwnd = GetTopWindow(HWND_DESKTOP);
	while ((mainwnd =::FindWindowEx(HWND_DESKTOP, mainwnd, CMainFrame::mainfrm_class_name, NULL)))
	{
		if (!::SendMessage(mainwnd, WM_QUERY_APPCONFIG, AC_MULTIPCMAN, 0) &&
			!::SendMessage(mainwnd, WM_QUERY_APPCONFIG, AC_PCMANLOCKED, 0))
		{
			if (*m_lpCmdLine)
			{
				int l = strlen(m_lpCmdLine) + 1;
				COPYDATASTRUCT d;
				d.lpData = m_lpCmdLine;
				d.cbData = l;
				d.dwData = 0;
				::SendMessage(mainwnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&d);
			}
			if (IsIconic(mainwnd))
				ShowWindow(mainwnd, SW_RESTORE);
			BringWindowToTop(mainwnd);
			SetForegroundWindow(mainwnd);
			return FALSE;
		}
	}

	// Initialize paths
	::GetModuleFileName(AfxGetInstanceHandle(), AppPath.GetBuffer(MAX_PATH), _MAX_PATH);
	AppPath.ReleaseBuffer();
	AppPath = AppPath.Left(AppPath.ReverseFind('\\') + 1);
	DefaultConfigPath = AppPath + CONFIG_DIR;

	/*
		// Test for PCMan 2004
		if( IsFileExist(DefaultConfigPath + "Config") )	// PCMan 2004
		{
			// Installed into the directory containing old config files.
			AfxMessageBox( IDS_PROMPT_IMPORT, MB_OK|MB_ICONINFORMATION );
			ShellExecute( NULL, "open", "http://pcman.openfoundry.org/faq.html", NULL, NULL, SW_SHOW );
		}
	*/
	// Supporting per-user settings under Windows NT/2000/xp/Vista
	if (IsWinNT() && !IsFileExist(AppPath + "Portable"))
	{
		BOOL ret = SHGetSpecialFolderPath(NULL, ConfigPath.GetBuffer(_MAX_PATH),
										  CSIDL_APPDATA, TRUE);
		ConfigPath.ReleaseBuffer();
		if (ret)
		{
			LPCTSTR configFiles[] = {
				CONFIG_FILENAME, UI_FILENAME, FUS_FILENAME,
				BBS_FAVORITE_FILENAME, TOOLBAR_BMP_FILENAME, ICON_BMP_FILENAME,
#if defined(_COMBO_)
				WEB_ICON_BMP_FILENAME,
#endif
			};

#if defined (_COMBO_)
			ConfigPath += "\\PCMan Combo\\";
#else
			ConfigPath += "\\PCMan\\";
#endif

			if (!IsFileExist(ConfigPath))
				CreateDirectory(ConfigPath, NULL);

			/* Always copy config files, but DO NOT overwrite.  */
			for (int i = 0; i < sizeof(configFiles) / sizeof(configFiles[0]); i++)
				CopyFile(DefaultConfigPath + configFiles[i], ConfigPath + configFiles[i], TRUE);
		}
		else
			ConfigPath.ReleaseBuffer();
	}
	else
	{
		ConfigPath = DefaultConfigPath;
	}

#if defined (_COMBO_)
	//IShellUIHandle
	CCustomOccManager *pMgr = new CCustomOccManager;

	// Create an IDispatch class for extending the Dynamic HTML Object Model
//	m_pDispOM = new CImpIDispatch;
	//Drop target
//	m_pDropTarget = new CImpIDropTarget;

	// Set our control containment up but using our control container
	// management class instead of MFC's default
	AfxEnableControlContainer(pMgr);
#endif

	AppConfig.Load(ConfigPath + CONFIG_FILENAME);

#if defined(_COMBO_)
	// Lite version calls this function before showing popup menu to reduce startup time.
	// Combo version loads all search plugins here for search bar.
	SearchPluginCollection.LoadAll();
#endif

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	if (! pFrame->LoadFrame(IDR_MAINFRAME,
							WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
							NULL))
	{
		return FALSE;
	}

	//Register Hotkey
	BOOL r = RegisterHotKey(pFrame->m_hWnd, 1, AppConfig.pcman_hotkey_mod, AppConfig.pcman_hotkey);

	pFrame->view.OnInitialUpdate();

	if (AppConfig.save_session)	// open saved session if any
		pFrame->OpenLastSession();

	if (*m_lpCmdLine)	// open file or address passed in command line argument
		pFrame->OnNewConnectionAds(m_lpCmdLine);
	else	// otherwise, open homepage if no command line argument was passed
		pFrame->OpenHomepage();

	pFrame->SwitchToConn(0);

	//Restore Main Window Position
	AppConfig.mainwnd_state.Restore(pFrame->m_hWnd);
	pFrame->UpdateWindow();

//如果只允許執行一個 PCMan，則把User data設為1
	SetWindowLong(m_pMainWnd->m_hWnd, GWL_USERDATA, !AppConfig.multiple_instance);
	pFrame->OnAutoUpdate();
	return TRUE;
}

int CApp::ExitInstance()
{
#if defined (_COMBO_)
    int exitcode = g_webmanager->OnAppEnd();
    if (exitcode > 0)
    {
        return exitcode;
    }

    delete g_webmanager;
#endif

    WSACleanup();
    return CWinApp::ExitInstance();
}

BOOL CApp::OnIdle( LONG lCount )
{
#ifdef _COMBO_
    return g_webmanager->OnMessageLoopIdle() ? TRUE : FALSE;
#else
	// XXX(Robert): not sure if this is okay.
	return TRUE;
#endif
}

std::string CApp::GetConfigPath(const std::string &name) const
{
	return std::string((LPCTSTR)ConfigPath) + name;
}

CApp *CApp::GetInstance()
{
	return reinterpret_cast<CApp *>(AfxGetApp());
}

/////////////////////////////////////////////////////////////////////////////
// CApp message handlers


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	static char web[];
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnReport();
	afx_msg void OnWeb();
	afx_msg void OnWeb2();
	afx_msg void OnHelp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

char CAboutDlg::web[] = "http://pcman.ptt.cc/pcman_help.html";

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_MAIL, OnReport)
	ON_BN_CLICKED(IDC_WEB, OnWeb)
	ON_BN_CLICKED(IDC_WEB2, OnWeb2)
	ON_BN_CLICKED(IDB_HELP, OnHelp)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CApp message handlers


void CAboutDlg::OnReport()
{
	const char tracker[] = "http://rt.openfoundry.org/Foundry/Project/Tracker/?Queue=744";
#ifdef	_COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(tracker, TRUE);
#else
	ShellExecute(m_hWnd, "open", tracker, NULL, NULL, SW_SHOW);
#endif
}

void CAboutDlg::OnWeb()
{
	web[20] = 0;
#ifdef	_COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(web, TRUE);
#else
	ShellExecute(m_hWnd, "open", web, NULL, NULL, SW_SHOW);
#endif
	web[20] = 'p';
}

void CAboutDlg::OnWeb2()
{
	const char url[] = "http://pcman.openfoundry.org/";
#ifdef	_COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(url, TRUE);
#else
	ShellExecute(m_hWnd, "open", url , NULL, NULL, SW_SHOW);
#endif
}

void CAboutDlg::OnHelp()
{
#ifdef	_COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(web, TRUE);
#else
	if ((long)ShellExecute(m_hWnd, "open", AppPath + "pcman.html", NULL, NULL, SW_SHOWMAXIMIZED) <= 32)
		ShellExecute(m_hWnd, "open", web, NULL, NULL, SW_SHOWMAXIMIZED);
#endif
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CFile story;
	if (story.Open((AppPath + "story.txt"), CFile::modeRead))
	{
		DWORD size = story.GetLength();
		char* buf = new char[size+1];
		story.Read(buf, size);
		buf[size] = '\0';
		story.Close();
		GetDlgItem(IDC_EDIT)->SetWindowText(buf);
		delete []buf;
	}

	char buf1[0x100];

	wsprintf(buf1, "%s - %d.%d.%d (Novus), Build %d, %s",
			 Version_InternalNameA, Version_Major, Version_Minor, Version_PatchLevel, Version_BuildNumber, Version_RevDateA);

	GetDlgItem(IDC_VERSION)->SetWindowText(buf1);
	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor == CTLCOLOR_STATIC && IDC_EDIT == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
//        pDC->SetBkColor( 0 );
//        pDC->SetTextColor( RGB(255, 255, 255) );
		return HBRUSH(COLOR_WINDOW + 1);
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

