#ifndef _PCMAN_COMBO_CLIENTDOWNLOADHANDLER_H_
#define _PCMAN_COMBO_CLIENTDOWNLOADHANDLER_H_


#include "include\cef_download_handler.h"

class ClientDownloadHandler :
    public CefDownloadHandler
{
    IMPLEMENT_REFCOUNTING(ClientDownloadHandler)
public:
    ClientDownloadHandler(void);
    virtual ~ClientDownloadHandler(void);

    virtual void OnBeforeDownload(
        CefRefPtr<CefBrowser> browser, 
        CefRefPtr<CefDownloadItem> download_item, 
        const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback) override;
};


#endif
