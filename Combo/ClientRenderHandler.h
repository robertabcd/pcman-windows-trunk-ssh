#ifndef _PCMAN_COMBO_CLIENTRENDERHANDLER_H_
#define _PCMAN_COMBO_CLIENTRENDERHANDLER_H_


#include "include\cef_render_handler.h"

class ClientRenderHandler :
    public CefRenderHandler
{
    IMPLEMENT_REFCOUNTING(ClientRenderHandler)
public:
    ClientRenderHandler(void);
    virtual ~ClientRenderHandler(void);

    virtual bool GetViewRect( CefRefPtr<CefBrowser> browser, CefRect& rect) override;

    virtual void OnPaint(
        CefRefPtr<CefBrowser> browser, 
        PaintElementType type, 
        const RectList &dirtyRects, const void *buffer, int width, int height) override;
};


#endif
