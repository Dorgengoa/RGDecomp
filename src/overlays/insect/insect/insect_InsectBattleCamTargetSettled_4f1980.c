#include "types.h"
/* insect 0x004F1980 -- 26 instructions, 8 float.  A three-slot deadband clamp.
 *
 * The slot is re-READ after the store (`lwc1 0x50($3)` then `lwc1 0x0($2)`
 * through the materialised element address) -- insect-load-across-store.
 * The final test is `c.eq.s $f1,$f0` with the VALUE in `fs`, which is the
 * implicit truth test `if (*p)` and not `*p != 0.0f`.
 *
 * D_0047D88C / D_0047D89C are gp floats (_gp 0x00485170 - 0x78E4 / - 0x78D4)
 * and must stay non-const to keep %gp_rel. */

typedef struct Obj {
    u8  pad000[0x50];
    f32 m50[3];                     /* +0x50 */
} Obj;

extern f32 D_0047D88C;
extern f32 D_0047D89C;

s32 insect_InsectBattleCamTargetSettled_4f1980(Obj *o)
{
    f32 *p;
    f32  lo;
    f32  hi;
    s32  i;

    hi = D_0047D88C;
    lo = D_0047D89C;
    for (i = 0; i < 3; i++) {
        p = &o->m50[i];
        if (lo <= *p && *p <= hi) {
            *p = 0.0f;
        }
        if (*p) {
            return 0;
        }
    }
    return 1;
}
