#ifndef _PCMAN_COMBO_NULLFRAME_H_
#define _PCMAN_COMBO_NULLFRAME_H_


#include "include\cef_frame.h"

class ClientHandlerBasic;
class NullFrame : public CefFrame
{
	IMPLEMENT_REFCOUNTING(NullFrame)

public:
	NullFrame(CefRefPtr<ClientHandlerBasic> client);
	virtual ~NullFrame(void);

	virtual bool IsValid() override;

	virtual void Undo() override;

	virtual void Redo() override;

	virtual void Cut() override;

	virtual void Copy() override;

	virtual void Paste() override;

	virtual void Delete() override;

	virtual void SelectAll() override;

	virtual void ViewSource() override;

	virtual void GetSource( CefRefPtr<CefStringVisitor> visitor ) override;

	virtual void GetText( CefRefPtr<CefStringVisitor> visitor ) override;

	virtual void LoadRequest( CefRefPtr<CefRequest> request ) override;

	virtual void LoadURL( const CefString& url ) override;

	virtual void LoadString( const CefString& string_val, const CefString& url ) override;

	virtual void ExecuteJavaScript( const CefString& code, const CefString& script_url, int start_line ) override;

	virtual bool IsMain() override;

	virtual bool IsFocused() override;

	virtual CefString GetName() override;

	virtual int64 GetIdentifier() override;

	virtual CefRefPtr<CefFrame> GetParent() override;

	virtual CefString GetURL() override;

	virtual CefRefPtr<CefBrowser> GetBrowser() override;

	virtual CefRefPtr<CefV8Context> GetV8Context() override;

	virtual void VisitDOM( CefRefPtr<CefDOMVisitor> visitor ) override;

private:
	CefRefPtr<ClientHandlerBasic> client_;
};


#endif
