#include "NullV8Exception.h"


NullV8Exception::NullV8Exception(void)
{
}


NullV8Exception::~NullV8Exception(void)
{
}

CefString NullV8Exception::GetMessage()
{
    return "";
}

CefString NullV8Exception::GetSourceLine()
{
    return "";
}

CefString NullV8Exception::GetScriptResourceName()
{
    return "";
}

int NullV8Exception::GetLineNumber()
{
    return -1;
}

int NullV8Exception::GetStartPosition()
{
    return -1;
}

int NullV8Exception::GetEndPosition()
{
    return 0;
}

int NullV8Exception::GetStartColumn()
{
    return -1;
}

int NullV8Exception::GetEndColumn()
{
    return -1;
}
