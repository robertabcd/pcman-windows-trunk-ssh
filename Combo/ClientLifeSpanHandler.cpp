#include "ClientLifeSpanHandler.h"

#include "CefUtil.h"

ClientLifeSpanHandler::ClientLifeSpanHandler(void) : browser_(nullptr), browser_id_(0)
{
}


ClientLifeSpanHandler::~ClientLifeSpanHandler(void)
{
}


void ClientLifeSpanHandler::OnAfterCreated( CefRefPtr<CefBrowser> browser )
{
    REQUIRE_UI_THREAD();

    if (0 == browser_id_)
    {
        AutoLock lock(this);
        if (0 == browser_id_)
        {
            browser_ = browser;
            browser_id_ = browser->GetIdentifier();
        }
    }
}


bool ClientLifeSpanHandler::DoClose( CefRefPtr<CefBrowser> browser )
{
    REQUIRE_UI_THREAD();

    if (this->GetBrowserId() == browser->GetIdentifier())
    {
        browser->GetHost()->ParentWindowWillClose();
    }

    return true;
}


void ClientLifeSpanHandler::OnBeforeClose( CefRefPtr<CefBrowser> browser )
{
    REQUIRE_UI_THREAD();

    if (this->GetBrowserId() == browser->GetIdentifier())
    {
        AutoLock lock(this);
        browser_ = nullptr;  //CefShutdown will throw exception when remove this line.
    }
}
