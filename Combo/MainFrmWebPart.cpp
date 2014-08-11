#include "WebConn.h"
#include "WebPageDlg.h"

#include "..\Lite\MouseCTL.h"
#include "..\Lite\StringDlg.h"
#include "..\Lite\Clipboard.h"
#include "..\Lite\MainFrm.h"

extern CUcs2Conv g_ucs2conv;

#if defined(_COMBO_)

BOOL CMainFrame::FilterWebConn(WebConn *web_conn)
{
	BOOL Close = FindAdFilter(
        web_conn->GetLocationName(), web_conn->GetLocationURL());

	if (Close)
    {
		PostMessage(WM_REMOVE_WEBCONN, 0, LPARAM(web_conn));
    }

	return Close;
}


void CMainFrame::OnNewHome()
{
    view.ConnectWeb("", TRUE);
    static_cast<WebConn *>(view.con)->GoHome();
}


void CMainFrame::OnWebPagePrint()
{
	if (!view.telnet || view.con)
	{
		static_cast<WebConn *>(view.con)->PrintPage();
	}
}


void CMainFrame::OnWebPageViewSrc()
{
    if (!view.telnet || view.con)
    {
		static_cast<WebConn *>(view.con)->ViewSrc();
    }
}


void CMainFrame::OnWebPagePrintSettings()
{
	if (!view.telnet || view.con)
	{
         static_cast<WebConn *>(view.con)->PrintSetting();
	}
}


void CMainFrame::OnWebPageSaveAs()
{
	if (!view.telnet || view.con)
	{
        static_cast<WebConn *>(view.con)->SaveAs();
	}
}


void CMainFrame::OnToolbarMenuDropDown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTOOLBAR nmtb = (LPNMTOOLBAR)pNMHDR;
	RECT rc;
	toolbar.SendMessage(TB_GETRECT, nmtb->iItem, (LPARAM)&rc);
	::MapWindowPoints(toolbar.m_hWnd, NULL, LPPOINT(&rc), 2);
	if (nmtb->iItem == ID_NEW_WWW)
	{
		HMENU pop =::GetSubMenu(::GetSubMenu(main_menu, 0), 0);
		TrackPopupMenu(pop, TPM_LEFTALIGN | TPM_TOPALIGN, rc.left, rc.bottom, 0, m_hWnd, NULL);
	}
	else
	{
		if (!view.con || !view.con->is_web)
			return;
		CMenu pop;
		WebConn *web_conn = static_cast<WebConn *>(view.con);
		pop.CreatePopupMenu();
        if (web_conn->IsTravelLogEmpty())
        {
            return;
        }

        std::vector<CString> travelLog;
        if (nmtb->iItem == ID_GOBACK)
        {
            travelLog = web_conn->TravelLogGoBack();
        }

        if (nmtb->iItem == ID_GOFORWARD)
        {
            travelLog = web_conn->TravelLogGoForward();
        }

        UINT id = 1;
        std::for_each(travelLog.begin(), travelLog.end(), [&pop, &id](const CString &title)
        {
            pop.AppendMenu(MF_STRING, id, title);
            id++;
        });

        id = pop.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_TOPALIGN, rc.left, rc.bottom, &view, NULL);
        if (id > 0)
        {
            if (nmtb->iItem == ID_GOBACK)
            {
                web_conn->GoBack(id);
            }

            if (nmtb->iItem == ID_GOFORWARD)
            {
                web_conn->GoForward(id);
            }
        }
    }
}


void CMainFrame::OnGoBack()
{
	if (view.con && view.con->is_web)
    {
        static_cast<WebConn *>(view.con)->GoBack(1);
    }
}


void CMainFrame::OnGoForward()
{
	if (view.con && view.con->is_web)
    {
        static_cast<WebConn *>(view.con)->GoForward(1);
    }
}


void CMainFrame::OnWebPageAddToAdFilter()
{
	if (view.telnet || !view.con)
    {
		return;
    }

	WebConn *web_conn = static_cast<WebConn *>(view.con);
	CAdItem item;
	item.title = web_conn->GetLocationName();
	item.url = web_conn->GetLocationURL();

	if (item.DoModal() == IDOK)
	{
		AppConfig.webpage_filter.Add(item.title + '\t' + item.url);
		FilterWebConn(web_conn);
	}
}


void CMainFrame::OnWebHome()
{
	if (view.con)
	{
		if (!view.telnet)
		{
			static_cast<WebConn *>(view.con)->GoHome();
			return;
		}
	}
	view.ConnectWeb("", TRUE)->GoHome();
}


void CMainFrame::OnSearchBarCancel()
{
	if (view.con && view.con->is_web)
    {
		static_cast<WebConn *>(view.con)->SetFocus();
    }
	else
    {
		view.SetFocus();
    }
}


void CMainFrame::OnBrowserFontSize(UINT id)
{
	if (view.con && view.con->is_web)
	{
		id -= ID_FONT_SMALLEST;
        static_cast<WebConn *>(view.con)->SetFontSize(id);
	}
}


void CMainFrame::LoadWebFavorites() //FIXME
{
	char title[32];
	GetMenuString(main_menu, 4, title, 32, MF_BYPOSITION);

	if (AppConfig.use_ie_fav)
		AppConfig.favorites.LoadIEFav(web_fav_menu);
	else
	{
		if (!IsFileExist(ConfigPath + WWW_FAVORITE_FILENAME))
			ImportIEFavorites();
		AppConfig.favorites.LoadFavorites(web_fav_menu, 'w');
	}

	ModifyMenu(main_menu, 4, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT)web_fav_menu, title);
}

#endif


void CMainFrame::OnAddressBarComboOK()
{
	CString address;
	int i = address_bar.GetCurSel();
	if (i == CB_ERR)
    {
		address_bar.GetWindowText(address);
    }
	else
    {
		address_bar.GetLBText(i, address);
    }

	int p = address.ReverseFind('\t');
	if (p != -1)
    {
		address = address.Left(p);
    }

#if defined(_COMBO_)
	// FIXME: We doesn't check for *.ans file here!!
	if (!AppConfig.ads_open_new && strncmp("telnet://", address, 9) && view.con && !view.telnet)
	{
        static_cast<WebConn *>(view.con)->Navigate(address);
		static_cast<WebConn *>(view.con)->SetFocus();
		return;
	}
#endif

	OnNewConnectionAds(address);
}


void CMainFrame::OnAddressComboCancel()
{
#if defined(_COMBO_)
	if (view.con && view.con->is_web)
    {
		static_cast<WebConn *>(view.con)->SetFocus();
    }
	else
#endif
    {
		view.SetFocus();
    }
	UpdateAddressBar();
}



void CMainFrame::OnUpdatePaste(CCmdUI *pCmdUI)
{
	if (!pCmdUI->m_pMenu)	// don't disable toolbar
    {
		return;
    }

#ifdef _COMBO_
	BOOL sel;
	if (view.con)
	{
		if (view.con->is_web)
        {
			sel = static_cast<WebConn *>(view.con)->CanPaste() ? TRUE : FALSE;
        }
		else
        {
			sel = (view.telnet->is_ansi_editor || view.telnet->is_connected);
        }
	}
	else
    {
		sel = FALSE;
    }

	pCmdUI->Enable(sel);
#else
	pCmdUI->Enable(view.telnet ? (view.telnet->is_ansi_editor || view.telnet->is_connected) : 0);
#endif
}


void CMainFrame::OnUpdateIsSel(CCmdUI *pCmdUI)
{
	// don't disable toolbar, or the icons will be grey and very ugly.
	if (!pCmdUI->m_pMenu)
	{
        return;
    }

#if defined(_COMBO_)
	BOOL sel;
	if (view.con)
	{
		if (view.con->is_web)
        {
            sel = static_cast<WebConn *>(view.con)->CanCopy() ? TRUE : FALSE;
        }
		else
        {
			sel = (view.telnet->sel_start != view.telnet->sel_end);
        }
	}
	else
    {
		sel = FALSE;
    }

	pCmdUI->Enable(sel);
#else
	pCmdUI->Enable(view.telnet && view.telnet->sel_start != view.telnet->sel_end);
#endif
}

void CMainFrame::OnShowFrequentlyUsedStr()
{
	CStringDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
#ifdef _COMBO_
		if (!view.con || dlg.str.IsEmpty())
        {
			return;
        }

		if (view.con->is_web)
        {
            static_cast<WebConn *>(view.con)->PasteText(dlg.str);
        }
		else
        {
            SendFreqStr(dlg.str, HIBYTE(HIWORD(dlg.inf)));
        }
#else
		if (!view.telnet || dlg.str.IsEmpty())
        {
			return;
        }

        SendFreqStr(dlg.str, HIBYTE(HIWORD(dlg.inf)));
#endif
	}

	if (dlg.data_changed)
    {
		LoadFrequentlyUsedStr();
    }
}


void CMainFrame::OnEditFind()
{
#ifdef	_COMBO_
	if (!view.con)
    {
		return;
    }

	if (view.con->is_web)
	{
		static_cast<WebConn *>(view.con)->ShowFindDialog();
		return;
	}
#else
	if (!view.telnet)
    {
		return;
    }
#endif
	view.FindStart();
}


void CMainFrame::OnFrequentlyUsedStr(UINT id)
{
	id -= ID_FIRST_HOTSTR;
#if	defined	_COMBO_
	if (!view.con)
    {
		return;
    }
#endif

	if (!view.telnet)
	{
#if	defined	_COMBO_
		if (id == 4)	//F5 key
        {
			static_cast<WebConn *>(view.con)->Refresh();
        }
		else
        {
            static_cast<WebConn *>(view.con)->PasteText(hotstr.ElementAt(id));
        }
#endif
		return;
	}

	CString str = hotstr.ElementAt(id);
	BYTE inf = hotstr_inf.ElementAt(id);
	SendFreqStr(str, inf);
}


void CMainFrame::OnCopy()
{
	CTelnetConn* telnet = view.telnet;
	if (!telnet)
	{
#if defined	_COMBO_
		CConn* con = view.con;
		if (con)
		{
            static_cast<WebConn *>(view.con)->CopySelectionToClipboard();
		}
#endif
		return;
	}

	view.CopySelText();
}


void CMainFrame::OnPaste()
{
	if (!view.telnet)
	{
#if defined	_COMBO_
		if (view.con)
		{
            static_cast<WebConn *>(view.con)->PasteFromClipboard();
		}
#endif
		return;
	}

	CString text;
	if (!CClipboard::GetText(text))
		return;

	//偵測是否包含色彩碼
	//如果有色彩碼，改成彩色貼上
	if (IsContainAnsiCode(text))
		view.SendAnsiString(text);
	else	//否則正常貼上純文字
	{
		//並且如果不包含色彩碼，再重新從剪貼簿取一次字串 (改取Unicode字串)

		wchar_t* pwstr = NULL;
		if (CClipboard::GetTextW(&pwstr))
		{
			UINT cp_id = view.GetCodePage();
			int len = wcslen(pwstr) * sizeof(wchar_t) + 1;
			char* pstr = new char[ len ];
			memset(pstr, 0, len);

			if (cp_id == 950)
			{
				g_ucs2conv.Ucs22Big5(pwstr, pstr);
			}
			else
			{
				::WideCharToMultiByte(cp_id, 0, pwstr, -1, pstr, len, NULL, NULL);
			}

			text.Empty();
			text = pstr;
			if (pstr)
				delete [] pstr;
			if (pwstr)
				delete [] pwstr;
			//考慮到 server 端實際接收資料的速度不快，
			//所以這邊試圖忽略掉從剪貼簿取兩次資料的開銷損失
		}
		view.telnet->SendString(text);
	}
}


void CMainFrame::OnSelAll()
{
	if (!view.telnet)
	{
#if defined	_COMBO_
		if (view.con)
		{
			 static_cast<WebConn *>(view.con)->SelectAll();
		}
#endif
		return;
	}
	SCROLLINFO info;
	view.GetScrollInfo(SB_VERT, &info);

	CTelnetConn *telnet = view.telnet;
	telnet->sel_start.x = 0;
	telnet->sel_start.y = info.nPos;
	telnet->sel_end.x = telnet->site_settings.cols_per_page;
	telnet->sel_end.y = info.nPos + telnet->site_settings.lines_per_page - 1;
	view.Invalidate(FALSE);
}


void CMainFrame::OnNciku()
{
	CTelnetConn* telnet = view.telnet;
	if (!telnet)
	{
#if defined	_COMBO_
		CConn* con = view.con;
		if (con)
		{
            static_cast<WebConn *>(view.con)->CopySelectionToClipboard();
		}
#endif
		return;
	}
	CString tmp = "http://www.nciku.com.tw/search/all/"+view.GetSelText();
#if defined _COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(tmp, TRUE);
#else
	ShellExecute(m_hWnd, "open", tmp, NULL, NULL, SW_SHOWMAXIMIZED);
#endif
}


void CMainFrame::OnWikipedia()
{
	CTelnetConn* telnet = view.telnet;
	if (!telnet)
	{
#if defined	_COMBO_
		CConn* con = view.con;
		if (con)
		{
            static_cast<WebConn *>(view.con)->CopySelectionToClipboard();
		}
#endif
		return;
	}
	CString tmp = "http://zh.wikipedia.org/wiki/"+view.GetSelText();
#if defined _COMBO_
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->view.ConnectWeb(tmp, TRUE);
#else
	ShellExecute(m_hWnd, "open", tmp, NULL, NULL, SW_SHOWMAXIMIZED);
#endif
}


void CMainFrame::UpdateUI()
{
	if (view.telnet)
	{
		CReBarCtrl& rbc = rebar.GetReBarCtrl();
		if (AppConfig.use_ansi_bar || view.telnet->is_ansi_editor)
			rbc.ShowBand(rbc.IDToIndex(2), TRUE);
		else
			rbc.ShowBand(rbc.IDToIndex(2), FALSE);
#if defined	_COMBO_
		progress_bar.ShowWindow(SW_HIDE);
#endif
	}
	else
	{
		CReBarCtrl& rbc = rebar.GetReBarCtrl();
		if (AppConfig.use_ansi_bar)
			rbc.ShowBand(rbc.IDToIndex(2), TRUE);
		else
			rbc.ShowBand(rbc.IDToIndex(2), FALSE);

		view.ShowScrollBar(SB_VERT, AppConfig.site_settings.showscroll);
#if defined	_COMBO_
		if (view.con)
		{
			progress_bar.SetRange32(0, static_cast<WebConn *>(view.con)->LoadingStatusMaxValue());
			progress_bar.SetPos(static_cast<WebConn *>(view.con)->LoadingStatusNowValue());
			progress_bar.ShowWindow(SW_SHOW);
		}
		else
			progress_bar.ShowWindow(SW_HIDE);
#endif
	}
	view.SetScrollBar();
}


void CMainFrame::OnFavorite(UINT id) //FIXME
{
	CTelnetConn* telnet = view.telnet;

	int idir = -1, _idir;	int level = 0;
	CString dir;

	const char sep_char = '\\' ;

	CStringArray* fav;
#ifdef _COMBO_
	BOOL bWWW = id >= ID_FIRST_WEB_FAVORITE;
	fav = bWWW ? &AppConfig.favorites.web_fav : &AppConfig.favorites.bbs_fav;
	id -= bWWW ? ID_FIRST_WEB_FAVORITE : ID_FIRST_BBS_FAVORITE;
#else
	fav = &AppConfig.favorites.bbs_fav;
	id -= ID_FIRST_BBS_FAVORITE;
#endif

	for (_idir = id; _idir >= 0; _idir--)
	{
		for (; _idir >= 0; _idir--)
		{
			if (fav->ElementAt(_idir).IsEmpty())
				level--;
			else if (fav->ElementAt(_idir)[0] == 'd')
			{
				if (level == 0)
				{
					if (idir == -1)
						idir = _idir;
					dir = (LPCTSTR(fav->ElementAt(_idir)) + 1) + (sep_char + dir);
					break;
				}
				level++;
			}
		}
	}
#ifdef _COMBO_
	if (bWWW)
		dir = (AppConfig.use_ie_fav ? CFavMenu::GetIEFavDir() : LoadString(IDS_WWW_FAVORITE_NAME)) + (sep_char + dir);
	else
#endif
		dir = (LoadString(IDS_BBS_FAVORITE_NAME) + (PATH_SEPARATOR + dir));

	CString name = fav->ElementAt(id);
#ifdef _COMBO_
	if (name[0] != 's' && name[0] != 'w')
#else
	if (name[0] != 's')
#endif
	{
		switch (name[0])
		{
		case 'a':
			{
#ifdef _COMBO_
				if (!view.con)
					return;
				if (bWWW)
				{
					if (view.con->is_web)
					{
						CWebPageDlg dlg(this);
						dlg.m_URL = static_cast<WebConn *>(view.con)->GetLocationURL();
						dlg.m_Name = view.con->name;
						if (dlg.DoModal() == IDOK)
						{
							if (AppConfig.use_ie_fav)
							{
								LPSTR pstr = (LPSTR)(LPCTSTR)dlg.m_Name;
								while (*pstr)
								{
									//check illegal filename except DBCS
									if (*pstr >= '\x81' && *pstr <= '\xfe') //0x81 to 0xfe (Big5)
									{
										pstr++;
										if (! *pstr)
											break;
									}
									else if (*pstr == '\\' || *pstr == '/' || *pstr == ':'
										|| *pstr == '?' || *pstr == '<' || *pstr == '>'
										|| *pstr == '|' || *pstr == '*' || *pstr == '\"')
										*pstr = '-';
									pstr++;
								}
								WritePrivateProfileString("InternetShortcut", "URL", dlg.m_URL, dir + dlg.m_Name + ".url");
							}
							else
							{
								name = 'w';
								name += dlg.m_Name;
								name += '\t';
								name += dlg.m_URL;
								fav->InsertAt(id - 1, name);
								AppConfig.favorites.SaveFavorites(FALSE);
							}
							LoadWebFavorites();
						}
					}
				}
				else
#endif
					if (telnet && !telnet->is_web && !telnet->is_ansi_editor)
					{
						name = 's';	name += telnet->name;
						name += '\t';
#ifdef _COMBO_
						name += telnet->address.Mid(9);
#else
						name += telnet->address;
#endif
						if (telnet->port != 23 && telnet->port > 0)
						{
							char port_str[16];
							sprintf(port_str, ":%d", telnet->port);
							name += port_str;
						}
						fav->InsertAt(id - 1, name);
						AppConfig.favorites.SaveFavorites(TRUE);
						LoadBBSFavorites();
					}
			}
			break;
		case 'e':
			{
				CString strPath = dir.Left(dir.GetLength() - 1);
#ifdef	_COMBO_
				if (bWWW && AppConfig.use_ie_fav)
				{
					typedef	DWORD (WINAPI DOFD)(HWND, LPCTSTR);
					DOFD* pfunc = NULL;
					HMODULE hmod = LoadLibrary("IEFRAME.dll");
					if (!hmod) hmod = LoadLibrary("Shdocvw.dll");
					pfunc = (DOFD*)GetProcAddress(hmod, "DoOrganizeFavDlg");
					if (!hmod || !pfunc)
						return;
					pfunc(m_hWnd, LPCTSTR(strPath));
					FreeLibrary(hmod);
					LoadWebFavorites();
				}
				else
#endif
				{
					CListDlg dlg(&view);
					dlg.m_InitPath = strPath;
					dlg.DoModal();
				}
				break;
			}
		case 'o':
			{
				id -= 2;
				for (level = 0, idir++; idir < int(id) ; idir++)
				{
					if (*LPCTSTR(fav->ElementAt(idir)) == 'd')
					{
						level++;
						continue;
					}
					else if (fav->ElementAt(idir) == "-")
					{
						level--;
						idir += 4;
						continue;
					}
					if (level == 0)
						view.ConnectStr(fav->ElementAt(idir), dir);
				}
			}
			break;
		}
		return;
	}

	view.ConnectStr(name, dir);
}


void CMainFrame::SwitchToConn(int index)
{
	CConn *newcon = tab.GetCon(index);

	MouseCTL_Reset();

#ifdef	_COMBO_
	prev_conn = view.con;
#else
	prev_conn = view.telnet;
	if (prev_conn)
	{
		if (prev_conn->is_telnet)
			reinterpret_cast<CTelnetConn*>(prev_conn)->is_getting_article = false;
		view.KillTimer(ID_MOVIETIMER);
	}
#endif

	if (!newcon)
	{
#if defined _COMBO_ //////////////////////
		view.con = NULL;
#endif /////////////////////////////////
		view.telnet = NULL;
		view.SetFocus();
		view.SetCaretPos(CPoint(view.left_margin, view.top_margin + view.lineh - 2));
		CRect &view_rect = view.view_rect;
		view.GetClientRect(view_rect);
		view.AdjustFont(view_rect.right, view_rect.bottom);
		UpdateUI();
		SetWindowText(CMainFrame::window_title + 3);
		UpdateAddressBar();
		UpdateStatus();
		view.Invalidate(FALSE);
#if defined	_COMBO_ ///////////////////
		view.ShowWindow(SW_SHOW);
#endif //////////////////////////////////
		return;
	}

#if defined _COMBO_ //////////////////////
	if (newcon == view.con)
		return;
#else
	if (newcon == view.telnet)
		return;
#endif /////////////////////////////////

	int idx = ConnToIndex(newcon);

	int cols_per_page = 0;
	int lines_per_page = 0;

#if defined _COMBO_/////////////////////////
	if (view.telnet)	//如果原本是BBS，記錄原本的行列數
	{
		cols_per_page = view.telnet->site_settings.cols_per_page;
		lines_per_page = view.telnet->site_settings.lines_per_page;
	}
	else	//如果原本是網頁，或是根本沒畫面
	{
		if (view.con)
		{
			static_cast<WebConn *>(view.con)->HideWindow();
		}
	}
	view.con = newcon;

	if (newcon->is_web)	//如果新畫面是WWW
	{
		view.telnet = NULL;
		view.GetWindowRect(view.view_rect);
		::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&view.view_rect, 2);
        static_cast<WebConn *>(view.con)->MoveWindow(view.view_rect, TRUE);
        static_cast<WebConn *>(view.con)->ShowWindow();

        view.ShowWindow(SW_HIDE);
	}
	else	//如果新畫面是BBS
	{
#endif///////////////////////////////////
		view.telnet = (CTelnetConn*)newcon;
		SetFocus();
		if (view.telnet->site_settings.cols_per_page != cols_per_page || view.telnet->site_settings.lines_per_page != lines_per_page)
		{
			CRect& view_rect = view.view_rect;
			view.GetClientRect(view_rect);
			view.AdjustFont(view_rect.right, view_rect.bottom);
		}
#if defined _COMBO_/////////////////////////
		view.ShowWindow(SW_SHOW);
#endif////////////////////////////////////
		view.Invalidate(FALSE);

		TCITEM item;
		item.mask = TCIF_IMAGE;
		if (view.telnet->is_connected)
		{
			item.iImage = 0;
			tab.SetItem(idx, &item);
		}
		view.telnet->UpdateCursorPos();
#if defined _COMBO_////////////////////////
	}
#endif///////////////////////////////////

	tab.SetCurSel(idx);
	UpdateStatus();
	UpdateAddressBar();
	UpdateStatus();
	UpdateUI();

	SetWindowText(newcon->name + CMainFrame::window_title);
}


#if 0
// XXX(Robert): this fails to compile.
void CMainFrame::OnIESetup() //FIXME
{
	typedef BOOL (WINAPI *IEOPTION)(HWND);
	HMODULE hmod = LoadLibrary("inetcpl.cpl");
	if (hmod)
	{
		IEOPTION SetIE = (IEOPTION)GetProcAddress(hmod, "LaunchInternetControlPanel");
		SetIE(m_hWnd);
		FreeLibrary(hmod);
	}
}
#endif