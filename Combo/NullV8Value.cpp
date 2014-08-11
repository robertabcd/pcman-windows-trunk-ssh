#include "NullV8Value.h"

#include "NullV8Exception.h"
#include "NullBase.h"
#include "NullV8Handler.h"

NullV8Value::NullV8Value(void)
{
}


NullV8Value::~NullV8Value(void)
{
}

bool NullV8Value::IsValid()
{
    return false;
}

bool NullV8Value::IsUndefined()
{
    return true;
}

bool NullV8Value::IsNull()
{
    return true;
}

bool NullV8Value::IsBool()
{
    return false;
}

bool NullV8Value::IsInt()
{
    return false;
}

bool NullV8Value::IsUInt()
{
    return false;
}

bool NullV8Value::IsDouble()
{
    return false;
}

bool NullV8Value::IsDate()
{
    return false;
}

bool NullV8Value::IsString()
{
    return false;
}

bool NullV8Value::IsObject()
{
    return false;
}

bool NullV8Value::IsArray()
{
    return false;
}

bool NullV8Value::IsFunction()
{
    return false;
}

bool NullV8Value::IsSame( CefRefPtr<CefV8Value> that )
{
    return false;
}

bool NullV8Value::GetBoolValue()
{
    return false;
}

int32 NullV8Value::GetIntValue()
{
    return 0;
}

uint32 NullV8Value::GetUIntValue()
{
    return 0;
}

double NullV8Value::GetDoubleValue()
{
    return 0.0;
}

CefTime NullV8Value::GetDateValue()
{
    return CefTime();
}

CefString NullV8Value::GetStringValue()
{
    return "";
}

bool NullV8Value::IsUserCreated()
{
    return false;
}

bool NullV8Value::HasException()
{
    return false;
}

CefRefPtr<CefV8Exception> NullV8Value::GetException()
{
    return new NullV8Exception;
}

bool NullV8Value::ClearException()
{
    return false;
}

bool NullV8Value::WillRethrowExceptions()
{
    return false;
}

bool NullV8Value::SetRethrowExceptions( bool rethrow )
{
    return false;
}

bool NullV8Value::HasValue( const CefString& key )
{
    return false;
}

bool NullV8Value::HasValue( int index )
{
    return false;
}

bool NullV8Value::DeleteValue( const CefString& key )
{
    return false;
}

bool NullV8Value::DeleteValue( int index )
{
    return false;
}

CefRefPtr<CefV8Value> NullV8Value::GetValue( const CefString& key )
{
    return this;
}

CefRefPtr<CefV8Value> NullV8Value::GetValue( int index )
{
    return this;
}

bool NullV8Value::SetValue( const CefString& key, CefRefPtr<CefV8Value> value, PropertyAttribute attribute )
{
    return false;
}

bool NullV8Value::SetValue( int index, CefRefPtr<CefV8Value> value )
{
    return false;
}

bool NullV8Value::SetValue( const CefString& key, AccessControl settings, PropertyAttribute attribute )
{
    return false;
}

bool NullV8Value::GetKeys( std::vector<CefString>& keys )
{
    return false;
}

bool NullV8Value::SetUserData( CefRefPtr<CefBase> user_data )
{
    return false;
}

CefRefPtr<CefBase> NullV8Value::GetUserData()
{
    return new NullBase;
}

int NullV8Value::GetExternallyAllocatedMemory()
{
    return 0;
}

int NullV8Value::AdjustExternallyAllocatedMemory( int change_in_bytes )
{
    return 0;
}

int NullV8Value::GetArrayLength()
{
    return 0;
}

CefString NullV8Value::GetFunctionName()
{
    return "";
}

CefRefPtr<CefV8Handler> NullV8Value::GetFunctionHandler()
{
    return new NullV8Handler;
}

CefRefPtr<CefV8Value> NullV8Value::ExecuteFunction( CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments )
{
    return this;
}

CefRefPtr<CefV8Value> NullV8Value::ExecuteFunctionWithContext( CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments )
{
    return this;
}
