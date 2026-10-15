#include "types.h"
/* normal 0x004F8EB0 -- the overlay's copy of main's FUN_00298B00: five
 * parameters, only the FIFTH ($8, EABI) is read, $4 is overwritten with
 * &D_004DB150 in the prologue and the `beql $4,$0` / `beqz $4` pair is the
 * null test on that array address, which mwcc does NOT fold away. */

extern u8 D_004DB150[];

extern void func_26F620(u8 *p, s32 b, s32 c, s32 d, s32 e);
extern void func_26F600(u8 *p);

extern s32 normal_TextClipRectDrawCb_4f8eb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 normal_TextClipRectDrawCb_4f8eb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    u8 *p;

    p = D_004DB150;
    if (a4 != 0) {
        if (p != 0) {
            func_26F620(p, 0, 0x200, 0x54, 0xD8);
        }
    } else {
        if (p != 0) {
            func_26F600(p);
        }
    }
    return 1;
}
