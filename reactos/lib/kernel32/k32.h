#define NTOS_MODE_USER
#include <ntos.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>
#include <ddk/ntddk.h>
#include <ddk/ntddbeep.h>
#include <ddk/ntddser.h>
#include <windows.h>
#include <ntdll/base.h>
#include <ntdll/rtl.h>
#include <ntdll/dbg.h>
#include <ntdll/csr.h>
#include <ntdll/ldr.h>
#include <napi/i386/segment.h>
#include <napi/teb.h>
#include <napi/npipe.h>
#include <ntos/minmax.h>
#include <csrss/csrss.h>
#include <reactos/buildno.h>
#include <rosrtl/thread.h>
#include <rosrtl/string.h>

#include "include/kernel32.h"
