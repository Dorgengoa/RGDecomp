#include "types.h"
#pragma tailcall off

/* mwcc at -O4 turns this into a tail `j`; retail keeps the frame and the
   `jal`, with both delay slots filled.  `#pragma tailcall off` is the only
   thing in the 244-name pragma namespace that reproduces it -- the four
   optimization_level settings give either the tail call (3, 4) or an
   unscheduled 9-word frame (1, 2). */

extern s32 _sceSifLoadElfPart(void *, void *, void *, s32);

void sceSifLoadElfPart(void *p0, void *p1, void *p2)
{
    _sceSifLoadElfPart(p0, p1, p2, 1);
}
