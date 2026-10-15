#include "types.h"
/* insect 0x005156D0 -- 244 bytes, 61 instructions, no calls.  A shortest-arc
 * angle step.  The `% 360` divisor is a constant, so mwcc emits a bare
 * `div $0,$5,$3` with NO zero trap and the divbyzerocheck pragma is not
 * needed.  The three arms all re-read 0xC4 / 0xC0, which retail CSEs into
 * $f3 / $f4; the divisor is one named local because it is hoisted above the
 * whole branch tree. */

typedef struct Obj {
    u8  pad000[0xC0];
    f32 mC0;                        /* +0xC0 */
    f32 mC4;                        /* +0xC4 */
    f32 mC8;                        /* +0xC8 */
    u8  padCC[0xE4 - 0xCC];
    f32 mE4;                        /* +0xE4 */
} Obj;

void insect_InsectPieceSetYawTarget_5156d0(Obj *o, f32 ang, f32 spd)
{
    f32 cur;
    f32 tgt;
    f32 d;
    f32 k;

    o->mC4 = (f32)((s32)ang % 360);
    cur = o->mC0;
    tgt = o->mC4;
    d = tgt - cur;
    if (spd <= 0.0f) {
        spd = 1.0f;
    }
    k = spd / o->mE4;
    if (d > 180.0f) {
        o->mC8 = (tgt - 360.0f - cur) / k;
    } else if (d < -180.0f) {
        o->mC8 = (360.0f + tgt - cur) / k;
    } else {
        o->mC8 = d / k;
    }
}
