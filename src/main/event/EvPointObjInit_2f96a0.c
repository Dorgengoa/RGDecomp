#include "types.h"

/* MAIN EvPointObjInit_2f96a0 -- EvObjSwitchInit_2f89f0 with EvObjResetThunk_2f9eb0 in place of
   EvObjSwitchReset_2f8b20. */

extern void EvObjResetThunk_2f9eb0(s32, s32, void *, void *, s32, s32);
extern s32 EvObjInit_2f9cf0(s32, s32, void *, void *, s32, s32);

s32 EvPointObjInit_2f96a0(s32 a, s32 b, void *c, void *d, s32 e, s32 f)
{
    EvObjResetThunk_2f9eb0(a, b, c, d, e, f);
    if (c == 0 || d == 0) {
        return 0;
    }
    return EvObjInit_2f9cf0(a, b, c, d, e, f);
}
