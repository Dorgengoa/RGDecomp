#include "types.h"

/* MSL C++ runtime: void operator delete(void *p) throw() { free(p); }
   Built as C++ with exceptions on: the empty throw() spec makes mwcc emit a
   frame-pointer frame plus an unreachable handler that calls __unexpected
   (retail EhUnexpected_1014d0, config/aliases.txt) and spins.  Retail carries no EH
   table for it, so objfix drops .exceptix/.exception (config/objfix.txt).
   Built -O4,p (config/toolchain.txt): the `b; nop` over the dead handler. */
#pragma cplusplus on
#pragma exceptions on

extern "C" void Free_130e30(void *);

extern "C" void OperatorDelete_100840(void *p) throw()
{
    Free_130e30(p);
}
