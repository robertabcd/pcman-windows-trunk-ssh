#ifndef _PCMAN_COMBO_NULLBROWSER_H_
#define _PCMAN_COMBO_NULLBROWSER_H_

#include "include/cef_browser.h"

class ClientHandlerBasic;
class NullBrowser : public CefBrowser
{
	IMPLEMENT_REFCOUNTING(NullBrowser)

public:
	NullBrowser(CefRefPtr<ClientHandlerBasic> client);
	virtual ~NullBrowser(void);

	virtual CefRefPtr<CefBrowserHost> GetHost() override;

	virtual bool CanGoBack() override;

	virtual void GoBack() override;

	virtual bool CanGoForward() override;

	virtual void GoForward() override;

	virtual bool IsLoading() override;

	virtual void Reload() override;

	virtual void ReloadIgnoreCache() override;

	virtual void StopLoad() override;

	virtual int GetIdentifier() override;

	virtual bool IsSame( CefRefPtr<CefBrowser> that ) override;

	virtual bool IsPopup() override;

	virtual bool HasDocument() override;

	virtual CefRefPtr<CefFrame> GetMainFrame() override;

	virtual CefRefPtr<CefFrame> GetFocusedFrame() override;

	virtual CefRefPtr<CefFrame> GetFrame( int64 identifier ) override;

	virtual CefRefPtr<CefFrame> GetFrame( const CefString& name ) override;

	virtual size_t GetFrameCount() override;

	virtual void GetFrameIdentifiers( std::vector<int64>& identifiers ) override;

	virtual void GetFrameNames( std::vector<CefString>& names ) override;

	virtual bool SendProcessMessage( CefProcessId target_process, CefRefPtr<CefProcessMessage> message ) override;

private:
    CefRefPtr<CefFrame> CreateNullFrame() const;

	CefRefPtr<ClientHandlerBasic> client_;
};


#endif
