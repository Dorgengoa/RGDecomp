#include "types.h"
/* normal 0x0051ACB0 -- five-slot refresh.  `((a<<3)+a)<<2 - ((a<<3)+a)` is
 * ((a * 9) << 2) - a * 9.  The loop body is an if/else on `i == a` and mwcc emits the
 * equal side as the FALL-THROUGH of a `bnel`. */

extern void *D_00484710;          /* gp - 0xA60 */

extern void func_28FC90(void *w, s32 id, s32 v, s32 k);
extern void func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);

s32 normal_TransWarpRowHighlight_51acb0(s32 a)
{
    s32 i;

    func_28FC90(D_00484710, 0x75D3, ((a * 9) << 2) - a * 9, 0);
    for (i = 0; i < 5; i++) {
        if (i == a) {
            func_28F670(D_00484710, 0x75D2, 0, 0, 0, 0, i);
        } else {
            func_28F670(D_00484710, 0x75D2, 0x14F, 0x1B, 4, 3, i);
        }
    }
    return 1;
}
