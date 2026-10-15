#include "types.h"

extern void * MinimapFindForArea_1dcb50(s32);
extern void MinimapSetColor_324990(void *, s32, s32, s32, s32);
extern void MinimapSetScreenAnchorPos_324ca0(void *, s32, s32);
extern void MinimapSetSizeClamped_324960(void *, s32, s32);
extern void MinimapSetWinSize_324c50(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x11C];
    u8 m11C;
};

struct Obj0 *MinimapSetFullView_1d9ca0(s32 p0)
{
    struct Obj0 *r0;

    r0 = MinimapFindForArea_1dcb50(p0);
    if (r0 != 0) {
        r0->m11C = 2;
        MinimapSetColor_324990(r0, 0, 0, 0, 0x40);
        MinimapSetScreenAnchorPos_324ca0(r0, 0x10, 0x20);
        MinimapSetSizeClamped_324960(r0, 0x1E0, 0x1E0);
        MinimapSetWinSize_324c50(r0, 0x1E0, 0x180);
    }
}
