// WebScene.cpp : implementation file
//

#include "../Lite/stdafx.h"
#include "WebScene.h"

#include "ClientHandlerBasic.h"


// WebScene

IMPLEMENT_DYNAMIC(WebScene, CWnd)

WebScene::WebScene(CefRefPtr<ClientHandlerBasic> client) : m_client(client)
{
}

WebScene::~WebScene()
{
}


BEGIN_MESSAGE_MAP(WebScene, CWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
END_MESSAGE_MAP()



// WebScene message handlers
void WebScene::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (nType != SIZE_MINIMIZED)
    {
        if (CefWindowHandle hwnd = m_client->GetBrowser()->GetHost()->GetWindowHandle())
        {
            ::SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, SWP_NOZORDER);
        }
    }
}


int WebScene::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  Add your specialized creation code here

    return 0;
}
