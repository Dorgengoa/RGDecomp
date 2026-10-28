/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamEyeSettled_4f19f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F19F0 -- 104 bytes, 26 instructions.  Three f32 slots are snapped
 * to zero when they fall inside the [D_0047D89C, D_0047D88C] band, then
 * re-read; the function returns 1 only if all three are zero.
 *
 * Both gp floats are loaded ONCE, before the loop, into $f2/$f3 -- so they are
 * named locals, not member reads inside the body: written off the externs mwcc
 * re-issues the `lwc1 ..(gp)` at every compare (12 bad words).
 *
 * The last compare is `c.eq.s $f1, $f0` -- the VALUE in `fs` -- so the test is
 * the IMPLICIT truth test `if (*p)`, not `*p != 0.0f` (which puts the zero in
 * `fs`).  The two gp floats stay plain non-const externs to keep %gp_rel.
 *
 * DECLARATION order, not assignment order, picks the FPR: `lo` declared second
 * puts it in $f3 and `hi` in $f2 (4 bad); declared FIRST it takes $f3 anyway
 * and `hi` gets $f2 -- retail.  Swapping the two ASSIGNMENTS instead is a
 * different, still-wrong object (b6305eb3), and doing both is 2 bad. */

typedef struct Obj {
    u8  pad00[0x40];
    f32 f40[3];                     /* +0x40 */
} Obj;

extern f32 D_0047D88C;
extern f32 D_0047D89C;

s32 insect_InsectBattleCamEyeSettled_4f19f0(Obj *o)
{
    f32 *p;
    f32  lo;
    f32  hi;
    s32  i;

    hi = D_0047D88C;
    lo = D_0047D89C;
    for (i = 0; i < 3; i++) {
        p = &o->f40[i];
        if (lo <= *p && *p <= hi) {
            *p = 0.0f;
        }
        if (*p) {
            return 0;
        }
    }
    return 1;
}
