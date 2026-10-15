#include "types.h"

/* factory.bin overlay, 0x00502760 -- 176 bytes / 44 words, 4 branches, 2 calls.
 * Fill a four-halfword row/column span for a part: hand each axis to its own
 * helper, choosing which of the part's two extents is the axis length from
 * bit 0 of the orientation.
 *
 * * The float parameter consumed here arrives in `$f13`, so it is the SECOND
 *   float parameter; `$f12` is never written before `jal 005028C0` -- the
 *   FIRST float is passed straight through, the "call marshals neither"
 *   shape already recorded for `factory_FactoryPartCentreX_501e20`.
 * * `beqz $18 / bnel $17` into the same `daddu $2,$0,$0` block is the `||`
 *   join, the recorded factory lever.
 * * `dsll32 $7, $2, 24` / `dsra32 $7, $7, 24` off a plain `lb` is an s32
 *   local plus an explicit `(s8)` cast -- an s8 local is the measured null
 *   ([[normal-s16-cast-sign-extension]] at the byte width).
 * * The two extents swap between the calls: `m` picks 0x15 then 0x14 for the
 *   X axis and 0x14 then 0x15 for the Y axis.
 */

typedef struct Obj {
    u8 pad000[0x2A0];
} Obj;

typedef struct Shape {
    u8 pad00[0x14];
    s8 f14;
    s8 f15;
} Shape;

extern void factory_FactoryGridSpanX_5028c0(Obj *o, s16 *p, s16 *q, s32 n, f32 v);
extern void factory_FactoryGridSpanZ_502810(Obj *o, s16 *p, s16 *q, s32 n, f32 v);

s32 factory_FactoryPartFootprintRect_502760(Obj *o, s16 *r, Shape *s, s32 f, f32 x, f32 y)
{
    s32 m;
    s32 n;

    if (r == 0 || s == 0) {
        return 0;
    }
    m = f & 1;
    n = (m != 0) ? s->f15 : s->f14;
    factory_FactoryGridSpanX_5028c0(o, &r[2], r, (s8)n, x);
    n = (m != 0) ? s->f14 : s->f15;
    factory_FactoryGridSpanZ_502810(o, &r[3], &r[1], (s8)n, y);
    return 1;
}
