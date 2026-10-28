/* rgp:protos */
#define RGP_SELF_MenuPartyPanelIconSizesResetMaybe_29ddf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C4];
    s32 m4C4;
};

s32 MenuPartyPanelIconSizesResetMaybe_29ddf0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m4C4;
    UiSetSpriteSizeUvSize_28f670(t0, 0xD6, 0xE, 0xE, 0xE, 0xE, 1);
    t1 = p0->m4C4;
    UiSetSpriteSizeUvSize_28f670(t1, 0xD6, 0xE, 0xE, 0xE, 0xE, 6);
    return 0;
}
