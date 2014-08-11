#ifndef _PCMAN_COMBO_CLIENTHANDLER_H_
#define _PCMAN_COMBO_CLIENTHANDLER_H_

#include "include/cef_process_message.h"
#include "ClientHandlerBasic.h"

class ClientContextMenuHandler;
class ClientDialogHandler;
class ClientDisplayHandler;
class ClientDownloadHandler;
class ClientFocusHandler;
class ClientGeolocationHandler;
class ClientJSDialogHandler;
class ClientKeyboardHandler;
class ClientLifeSpanHandler;
class ClientLoadHandler;
class ClientRenderHandler;
class ClientRequestHandler;

class ClientHandler :
    public ClientHandlerBasic
{
public:
    ClientHandler(
        CefRefPtr<ClientContextMenuHandler> contextMenuHandler,
        CefRefPtr<ClientDialogHandler> dialogHandler,
        CefRefPtr<ClientDisplayHandler> displayHandler,
        CefRefPtr<ClientDownloadHandler> downloadHandler,
        CefRefPtr<ClientFocusHandler> focusHandler,
        CefRefPtr<ClientGeolocationHandler> geolocationHandler,
        CefRefPtr<ClientJSDialogHandler> jsdialogHandler,
        CefRefPtr<ClientKeyboardHandler> keyboardHandler,
        CefRefPtr<ClientLifeSpanHandler> lifeSpanHandler,
        CefRefPtr<ClientLoadHandler> loadHandler,
        CefRefPtr<ClientRenderHandler> renderHandler,
        CefRefPtr<ClientRequestHandler> requestHandler);
    virtual ~ClientHandler(void);

    virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;

    virtual CefRefPtr<CefDialogHandler> GetDialogHandler() override;

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;

    virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() override;

    virtual CefRefPtr<CefFocusHandler> GetFocusHandler() override;

    virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler() override;

    virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override;

    virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override;

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;

    virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override;

    virtual bool OnProcessMessageReceived( 
        CefRefPtr<CefBrowser> browser, 
        CefProcessId source_process, 
        CefRefPtr<CefProcessMessage> message ) override;

public:
    virtual CefRefPtr<CefBrowser> GetBrowser() override;
    virtual int GetBrowserId() override;

private:
    CefRefPtr<ClientContextMenuHandler> m_contextMenuHandler;
    CefRefPtr<ClientDialogHandler> m_dialogHandler;
    CefRefPtr<ClientDisplayHandler> m_displayHandler;
    CefRefPtr<ClientDownloadHandler> m_downloadHandler;
    CefRefPtr<ClientFocusHandler> m_focusHandler;
    CefRefPtr<ClientGeolocationHandler> m_geolocationHandler;
    CefRefPtr<ClientJSDialogHandler> m_jsdialogHandler;
    CefRefPtr<ClientKeyboardHandler> m_keyboardHandler;
    CefRefPtr<ClientLifeSpanHandler> m_lifeSpanHandler;
    CefRefPtr<ClientLoadHandler> m_loadHandler;
    CefRefPtr<ClientRenderHandler> m_renderHandler;
    CefRefPtr<ClientRequestHandler> m_requestHandler;

private:
    IMPLEMENT_REFCOUNTING(ClientHandler)

};


#endif
