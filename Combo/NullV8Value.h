#ifndef _PCMAN_COMBO_NULLV8VALUE_H_
#define _PCMAN_COMBO_NULLV8VALUE_H_


#include "include\cef_v8.h"

class NullV8Value : public CefV8Value
{
    IMPLEMENT_REFCOUNTING(NullV8Value)

public:
    NullV8Value(void);
    virtual ~NullV8Value(void);

    virtual bool IsValid() override;

    virtual bool IsUndefined() override;

    virtual bool IsNull() override;

    virtual bool IsBool() override;

    virtual bool IsInt() override;

    virtual bool IsUInt() override;

    virtual bool IsDouble() override;

    virtual bool IsDate() override;

    virtual bool IsString() override;

    virtual bool IsObject() override;

    virtual bool IsArray() override;

    virtual bool IsFunction() override;

    virtual bool IsSame( CefRefPtr<CefV8Value> that ) override;

    virtual bool GetBoolValue() override;

    virtual int32 GetIntValue() override;

    virtual uint32 GetUIntValue() override;

    virtual double GetDoubleValue() override;

    virtual CefTime GetDateValue() override;

    virtual CefString GetStringValue() override;

    virtual bool IsUserCreated() override;

    virtual bool HasException() override;

    virtual CefRefPtr<CefV8Exception> GetException() override;

    virtual bool ClearException() override;

    virtual bool WillRethrowExceptions() override;

    virtual bool SetRethrowExceptions( bool rethrow ) override;

    virtual bool HasValue( const CefString& key ) override;

    virtual bool HasValue( int index ) override;

    virtual bool DeleteValue( const CefString& key ) override;

    virtual bool DeleteValue( int index ) override;

    virtual CefRefPtr<CefV8Value> GetValue( const CefString& key ) override;

    virtual CefRefPtr<CefV8Value> GetValue( int index ) override;

    virtual bool SetValue( const CefString& key, CefRefPtr<CefV8Value> value, PropertyAttribute attribute ) override;

    virtual bool SetValue( int index, CefRefPtr<CefV8Value> value ) override;

    virtual bool SetValue( const CefString& key, AccessControl settings, PropertyAttribute attribute ) override;

    virtual bool GetKeys( std::vector<CefString>& keys ) override;

    virtual bool SetUserData( CefRefPtr<CefBase> user_data ) override;

    virtual CefRefPtr<CefBase> GetUserData() override;

    virtual int GetExternallyAllocatedMemory() override;

    virtual int AdjustExternallyAllocatedMemory( int change_in_bytes ) override;

    virtual int GetArrayLength() override;

    virtual CefString GetFunctionName() override;

    virtual CefRefPtr<CefV8Handler> GetFunctionHandler() override;

    virtual CefRefPtr<CefV8Value> ExecuteFunction( CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments ) override;

    virtual CefRefPtr<CefV8Value> ExecuteFunctionWithContext( CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments ) override;

};


#endif
