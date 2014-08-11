#include <shlobj.h> 
#include <string>

#include "ClientDownloadHandler.h"


ClientDownloadHandler::ClientDownloadHandler(void)
{
}


ClientDownloadHandler::~ClientDownloadHandler(void)
{
}

void ClientDownloadHandler::OnBeforeDownload( CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback )
{
    wchar_t buffer[MAX_PATH] = {0};
    SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, buffer); //CSIDL_DESKTOP //CSIDL_DESKTOPDIRECTORY
    
    std::wstring path(buffer);
    path += L"\\";
    path += suggested_name;

    callback->Continue(path, true);
}
