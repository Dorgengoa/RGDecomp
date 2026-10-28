/* rgp:protos */
#define RGP_SELF_TextClipRectDrawCb_298b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN TextClipRectDrawCb_298b00 -- five parameters, only the FIFTH ($8) is read; $4 is
   overwritten with &D_004DB150 in the prologue.  The `beql $4,$0` / `beqz $4`
   pair is a null test on that array address which mwcc does NOT fold away. */

/*rgp*/
/*rgp*/

extern u8 D_004DB150[];

s32 TextClipRectDrawCb_298b00(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    u8 *p;

    p = D_004DB150;
    if (a4 != 0) {
        if (p != 0) {
            TextStyleSetClipRect_26f620(p, 0, 0x200, 0x12, 0x52);
        }
    } else {
        if (p != 0) {
            TextStyleClearClipRect_26f600(p);
        }
    }
    return 1;
}
