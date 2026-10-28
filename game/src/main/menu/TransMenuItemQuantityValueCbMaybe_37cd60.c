/* rgp:protos */
#define RGP_SELF_TransMenuItemQuantityValueCbMaybe_37cd60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00484710;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 TransMenuItemQuantityValueCbMaybe_37cd60(struct Obj0 *p0)
{
    s32 r0;

    if (p0->m10 <= 0) {
        p0->m10 = 1;
    }
    r0 = ((s32)UiSetWidgetSubItemValue_291250(D_00484710, 0x7616, 0, (long long)(p0->m10)));
    return 1;
}
