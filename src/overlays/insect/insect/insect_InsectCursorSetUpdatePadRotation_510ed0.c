#include "types.h"
/* insect 0x00510ED0 -- 296 bytes, 74 instructions.
 *
 * MATCHED ix31.  The residue was five words at 0x510F84..0x510F94 and it is a
 * CSE, not a fabs spelling.  Retail negates d[2] IN PLACE (`neg.s $f1,$f1`),
 * which destroys the register holding d[2], so the else arm's later
 * `d[2] < 0.0f` test must RE-LOAD it -- and that reload is what fills the
 * branch-likely slot at 0x510F94, which is why retail's branch there is `bc1tl`
 * and ours was `bc1t` + `nop`.  We held ONE CSE'd load of d[2] alive in $f1
 * from 0x510F70 into the else arm, so the negation needed a second register
 * ($f0, via a `mov.s`) and the reload was unnecessary.  The same function
 * already does it retail's way for d[0] (in-place `neg.s $f2,$f2` at 0x510F6C
 * and a reload at 0x510F98, both matching) -- that asymmetry was the tell.
 *
 * `d[(u32)2]` breaks the CSE ([[levers.d/mwcc-index-cast-defeats-cse]]).  The
 * cast at EITHER read site gives the SAME object; `*(d + 2)`, a `(f32 *)` cast,
 * a named second local, and swapping the two fabs spellings are all inert or
 * worse (deck A 11 arms, deck B 12 arms, build/ix31/sweep_510ed0_*.log).
 */

typedef struct Obj {
    u8  pad00[0x40];
    f32 f40[4];                     /* +0x40 */
    f32 f50[4];                     /* +0x50 */
    s8  f60;                        /* +0x60 */
} Obj;

typedef struct Info {
    u8  pad00[0x18];
    s64 f18;                        /* +0x18 */
} Info;

extern Info *insect_InsectCursorSetGetCurPage_511e20(Obj *o);

void insect_InsectCursorSetUpdatePadRotation_510ed0(Obj *o)
{
    f32 d[3];
    f32 ax;
    f32 az;
    Info *p;
    s32 i;

    for (i = 0; i < 3; i++) {
        d[i] = o->f50[i] - o->f40[i];
    }
    p = insect_InsectCursorSetGetCurPage_511e20(o);
    if ((p->f18 & 0x10) != 0) {
        if (d[0] == 0.0f && d[2] == 0.0f) {
            o->f60 = 0;
            return;
        }
        if (d[0] < 0.0f) {
            ax = -d[0];
        } else {
            ax = d[0];
        }
        az = d[2];
        if (az < 0.0f) {
            az = -az;
        }
        if (ax > az) {
            if (d[0] < 0.0f) {
                o->f60 = 1;
            } else {
                o->f60 = 3;
            }
        } else {
            if (d[(u32)2] < 0.0f) {
                o->f60 = 4;
            } else {
                o->f60 = 2;
            }
        }
    } else {
        o->f60 = 0;
    }
}
