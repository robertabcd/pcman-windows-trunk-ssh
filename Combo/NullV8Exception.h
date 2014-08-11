#ifndef _PCMAN_COMBO_NULLV8EXCEPTION_H_
#define _PCMAN_COMBO_NULLV8EXCEPTION_H_


#include "include\cef_v8.h"

class NullV8Exception : public CefV8Exception
{
    IMPLEMENT_REFCOUNTING(NullV8Exception)

public:
    NullV8Exception(void);
    virtual ~NullV8Exception(void);

    virtual CefString GetMessage();

    virtual CefString GetSourceLine();

    virtual CefString GetScriptResourceName();

    virtual int GetLineNumber();

    virtual int GetStartPosition();

    virtual int GetEndPosition();

    virtual int GetStartColumn();

    virtual int GetEndColumn();

};


#endif
