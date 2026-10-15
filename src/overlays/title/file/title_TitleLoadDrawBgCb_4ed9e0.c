#include "types.h"

/* title.bin overlay, 0x004ED9E0 -- doubly guarded call whose inner argument
 * is a FLOAT returned in $f0 and moved straight into $f12.
 *
 * `beqz $8` tests the FIFTH argument ($8..$11 are arguments 5-8 on this ABI),
 * and the inner `beql` puts the epilogue restore in its delay slot, so the
 * call is the inline arm -- guard on the call, not on an early return.
 */

extern void *D_00484170;
extern float func_290770(void *a, s32 b);
extern void func_3768D0(void *o, float x);

s32 title_TitleLoadDrawBgCb_4ed9e0(void *o, s32 b, s32 c, s32 d, s32 e)
{
    void *p;

    if (e != 0) {
        p = D_00484170;
        if (p != 0) {
            func_3768D0(o, func_290770(p, 7));
        }
    }
    return 0;
}
