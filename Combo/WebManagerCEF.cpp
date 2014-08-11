#include "WebManagerCEF.h"

#include "ClientApp.h"
#include "ClientHandler.h"

#include "ClientContextMenuHandler.h"
#include "ClientDialogHandler.h"
#include "ClientDisplayHandler.h"
#include "ClientDownloadHandler.h"
#include "ClientFocusHandler.h"
#include "ClientGeolocationHandler.h"
#include "ClientJSDialogHandler.h"
#include "ClientKeyboardHandler.h"
#include "ClientLifeSpanHandler.h"
#include "ClientLoadHandler.h"
#include "ClientRenderHandler.h"
#include "ClientRequestHandler.h"

#include "WebConnCEF.h"


WebManagerCEF::WebManagerCEF(void)
{
}


WebManagerCEF::~WebManagerCEF(void)
{
}


int WebManagerCEF::OnAppStart(HINSTANCE instance)
{
    CefMainArgs main_args;
    CefRefPtr<ClientApp> app(new ClientApp);

    this->exitcode_ = CefExecuteProcess(main_args, app.get());
    if (this->exitcode_ < 0)
    {
        CefSettings settings;
        settings.multi_threaded_message_loop = false;
        //settings.multi_threaded_message_loop = true;
        CefInitialize(main_args, settings, app.get());
    }

    return this->exitcode_;
}


int WebManagerCEF::OnAppEnd()
{
    CefShutdown();
    return this->exitcode_;
}


bool WebManagerCEF::OnMessageLoopIdle()
{
    CefDoMessageLoopWork();
    return true;
}


WebConn *WebManagerCEF::Create()
{
    CefRefPtr<ClientContextMenuHandler> contextmenu_handler(new ClientContextMenuHandler);
    CefRefPtr<ClientDialogHandler> dialog_handler(new ClientDialogHandler);
    CefRefPtr<ClientDisplayHandler> display_handler(new ClientDisplayHandler);
    CefRefPtr<ClientDownloadHandler> download_handler(new ClientDownloadHandler);
    CefRefPtr<ClientFocusHandler> focus_handler(new ClientFocusHandler);
    CefRefPtr<ClientGeolocationHandler> geolocation_handler(new ClientGeolocationHandler);
    CefRefPtr<ClientJSDialogHandler> jsdialog_handler(new ClientJSDialogHandler);
    CefRefPtr<ClientKeyboardHandler> keyboard_handler(new ClientKeyboardHandler);
    CefRefPtr<ClientLifeSpanHandler> lifeSpan_handler(new ClientLifeSpanHandler);
    CefRefPtr<ClientLoadHandler> load_handler(new ClientLoadHandler);
    CefRefPtr<ClientRenderHandler> render_handler(new ClientRenderHandler);
    CefRefPtr<ClientRequestHandler> request_handler(new ClientRequestHandler);

    CefRefPtr<ClientHandlerBasic> client = new ClientHandler(
        contextmenu_handler, dialog_handler, display_handler,
        download_handler, focus_handler, geolocation_handler,
        jsdialog_handler, keyboard_handler, lifeSpan_handler,
        load_handler, render_handler, request_handler);

    return new WebConnCEF(client);
}
