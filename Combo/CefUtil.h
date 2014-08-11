#ifndef _PCMAN_COMBO_CEFUTIL_H_
#define _PCMAN_COMBO_CEFUTIL_H_

#include <cassert>
#include "include/cef_task.h"

#define REQUIRE_UI_THREAD()     assert(CefCurrentlyOn(TID_UI));
#define REQUIRE_IO_THREAD()     assert(CefCurrentlyOn(TID_IO));
#define REQUIRE_FILE_THREAD()   assert(CefCurrentlyOn(TID_FILE));

#endif
