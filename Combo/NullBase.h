#ifndef _PCMAN_COMBO_NULLBASE_H_
#define _PCMAN_COMBO_NULLBASE_H_


#include "include\cef_base.h"

class NullBase : public CefBase
{
    IMPLEMENT_REFCOUNTING(CefBase)

public:
    NullBase(void);
    virtual ~NullBase(void);
};


#endif
