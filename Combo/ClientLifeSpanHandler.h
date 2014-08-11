#ifndef _PCMAN_COMBO_CLIENTLIFESPANHANDLER_H_
#define _PCMAN_COMBO_CLIENTLIFESPANHANDLER_H_

#include <cassert>

#include "include\cef_life_span_handler.h"
#include "NullBrowser.h"

class ClientLifeSpanHandler :
    public CefLifeSpanHandler
{
    IMPLEMENT_REFCOUNTING(ClientLifeSpanHandler)
    IMPLEMENT_LOCKING(ClientLifeSpanHandler);
public:
    ClientLifeSpanHandler(void);
    virtual ~ClientLifeSpanHandler(void);

    virtual void OnAfterCreated( CefRefPtr<CefBrowser> browser ) override;

    virtual bool DoClose( CefRefPtr<CefBrowser> browser ) override;

    virtual void OnBeforeClose( CefRefPtr<CefBrowser> browser ) override;

public:
    void SetNullBrowser(CefRefPtr<NullBrowser> browser)
    {
        if (nullptr == browser_.get())
        {
            AutoLock lock(this);
            if (nullptr == browser_.get())
            {
                browser_ = browser;
            }
        }
    }


    CefRefPtr<CefBrowser> GetBrowser()
    {
        assert(browser_.get()); //forget SetNullBrowser.

        AutoLock lock(this);
        return browser_;
    }

    int GetBrowserId() const
    {
        return browser_id_;
    }

private:
    CefRefPtr<CefBrowser> browser_;
    int browser_id_;
};


#endif
