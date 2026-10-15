#include "types.h"

/* factory.bin overlay, 0x00505070 -- arm the shake and widen its amplitude,
 * keeping whatever sign the running amplitude already has.
 * 72 bytes, 18 instructions, 2 conditional branches, 0 calls -- a leaf with
 * NO stack frame.
 *
 * * Both `abs.s` are inline, so the magnitude is an intrinsic and not a call.
 *
 * * `bc1fl` skips with `swc1 $f1, 0x3F0($4)` in the LIKELY slot, so the
 * POSITIVE arm is the tail-duplicated one: the source is
 * `if (o->f3F0 < 0) neg; else pos;`, written in that order.
 */

typedef struct Obj {
    u8  pad000[0x3E8];
    s32 f3E8;
    s32 f3EC;
    f32 f3F0;
} Obj;

extern f32 fabsf(f32 x);

void factory_FactoryCameraShakeStart_505070(Obj *o, f32 v)
{
    o->f3E8 = 1;
    o->f3EC = 0;
    if (fabsf(o->f3F0) < fabsf(v)) {
        if (o->f3F0 < 0.0f) {
            o->f3F0 = -fabsf(v);
        } else {
            o->f3F0 = fabsf(v);
        }
    }
}
