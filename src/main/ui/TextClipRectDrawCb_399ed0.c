/* TextClipRectDrawCb_399ed0 -- shape-identical to merged TextClipRectDrawCb_298b00 (22 instructions); the donor's
   source with the symbol renamed, 0 call target(s) and 2 immediate(s) substituted:
     imm 18 -> 142
     imm 82 -> 382
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* MAIN TextClipRectDrawCb_399ed0 -- five parameters, only the FIFTH ($8) is read; $4 is
   overwritten with &D_004DB150 in the prologue.  The `beql $4,$0` / `beqz $4`
   pair is a null test on that array address which mwcc does NOT fold away. */

extern void TextStyleSetClipRect_26f620(u8 *, s32, s32, s32, s32);
extern void TextStyleClearClipRect_26f600(u8 *);

extern u8 D_004DB150[];

s32 TextClipRectDrawCb_399ed0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    u8 *p;

    p = D_004DB150;
    if (a4 != 0) {
        if (p != 0) {
            TextStyleSetClipRect_26f620(p, 0, 0x200, 0x8E, 0x17E);
        }
    } else {
        if (p != 0) {
            TextStyleClearClipRect_26f600(p);
        }
    }
    return 1;
}
