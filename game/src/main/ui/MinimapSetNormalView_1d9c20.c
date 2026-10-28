/* rgp:protos */
#define RGP_SELF_MinimapSetNormalView_1d9c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x11C];
    u8 m11C;
};

struct Obj0 *MinimapSetNormalView_1d9c20(s32 p0)
{
    struct Obj0 *r0;

    r0 = MinimapFindForArea_1dcb50(p0);
    if (r0 != 0) {
        r0->m11C = 0;
        MinimapSetColor_324990(r0, 0, 0, 0, 0);
        MinimapSetScreenAnchorPos_324ca0(r0, -1, -1);
        MinimapSetSizeClamped_324960(r0, 0x140, 0x140);
        MinimapSetWinSize_324c50(r0, 0xA0, 0x90);
    }
}
