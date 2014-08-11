#ifndef _PCMAN_COMBO_WEBSCENE_H_
#define _PCMAN_COMBO_WEBSCENE_H_

#include <afxwin.h>
#include "include/cef_base.h"

class ClientHandlerBasic;
// WebScene
class WebScene : public CWnd
{
    DECLARE_DYNAMIC(WebScene)

public:
    WebScene(CefRefPtr<ClientHandlerBasic> client);
    virtual ~WebScene();

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
    CefRefPtr<ClientHandlerBasic> m_client;
};



#endif
