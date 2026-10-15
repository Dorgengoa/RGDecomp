#include "types.h"

/* MAIN EvObjSwitchInit_2f89f0 -- forwards its six arguments to EvObjSwitchReset_2f8b20 and
   then, unless either pointer argument is null, to EvObjInit_2f9cf0.
   The two guards branch in OPPOSITE directions: that is an `||`. */

extern void EvObjSwitchReset_2f8b20(s32, s32, void *, void *, s32, s32);
extern s32 EvObjInit_2f9cf0(s32, s32, void *, void *, s32, s32);

s32 EvObjSwitchInit_2f89f0(s32 a, s32 b, void *c, void *d, s32 e, s32 f)
{
    EvObjSwitchReset_2f8b20(a, b, c, d, e, f);
    if (c == 0 || d == 0) {
        return 0;
    }
    return EvObjInit_2f9cf0(a, b, c, d, e, f);
}
