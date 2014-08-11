#include "ClientRenderHandler.h"


ClientRenderHandler::ClientRenderHandler(void)
{
}


ClientRenderHandler::~ClientRenderHandler(void)
{
}


bool ClientRenderHandler::GetViewRect( CefRefPtr<CefBrowser> browser, CefRect& rect )
{
    throw std::exception("The method or operation is not implemented.");
}


void ClientRenderHandler::OnPaint( 
    CefRefPtr<CefBrowser> browser, 
    PaintElementType type, 
    const RectList &dirtyRects, const void *buffer, int width, int height )
{
    throw std::exception("The method or operation is not implemented.");
}
