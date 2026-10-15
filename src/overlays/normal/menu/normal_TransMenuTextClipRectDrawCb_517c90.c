#include "types.h"
/* normal 0x00517C90 -- `lui 0x4E / addiu -0x4EB0` is the address 0x004DB150
 * compared against NULL and NOT folded, so the guard is on a pointer local.
 * `beqz $8` is the FIFTH integer parameter under the EABI. */

extern u8 D_004DB150[];

extern void func_26F620(u8 *p, s32 a, s32 b, s32 c, s32 d);
extern void func_26F600(void);

s32 normal_TransMenuTextClipRectDrawCb_517c90(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    u8 *p;

    p = D_004DB150;
    if (p == NULL) {
        return 0;
    }
    if (e != 0) {
        func_26F620(p, 0, 0x200, 0x12, 0x52);
        return 1;
    }
    func_26F600();
    return 1;
}
