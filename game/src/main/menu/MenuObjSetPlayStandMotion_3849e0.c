/* rgp:protos */
#define RGP_SELF_MenuObjSetPlayStandMotion_3849e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00463EC0[];

void MenuObjSetPlayStandMotion_3849e0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r3;

    r0 = BitArraySetReturnOld_384360((p0 + 0x4155), 1, 0);
    r1 = BitArraySetReturnOld_384360((p0 + 0x4155), 2, 0);
    l2 = 0;
    do {
        r3 = ((unsigned char)MenuObjSlotIsActive_3849d0(((p0 + (((l2 * 0x3C) + l2) << 5)) + 0x13B0)));
        if (r3 != 0) {
            ModelObjPlayMotionByName_1867a0(((p0 + (((l2 * 0x3C) + l2) << 5)) + 0x13C0), D_00463EC0, 0);
        }
        l2 = (l2 + 1);
    } while (l2 < 2);
}
