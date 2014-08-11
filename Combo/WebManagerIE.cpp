#include "WebManagerIE.h"

#include "WebConnIE.h"

WebManagerIE::WebManagerIE(void)
{
}


WebManagerIE::~WebManagerIE(void)
{
}

int WebManagerIE::OnAppStart(HINSTANCE)
{
    return -1;
}

int WebManagerIE::OnAppEnd()
{
    return -1;
}

bool WebManagerIE::OnMessageLoopIdle()
{
    return true;
}

WebConn * WebManagerIE::Create()
{
    return new WebConnIE;
}

