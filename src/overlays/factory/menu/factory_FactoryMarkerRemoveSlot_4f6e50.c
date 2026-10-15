#include "types.h"

/* factory.bin overlay, 0x004F6E50 -- lift one trail point out of the ring:
 * copy the record into the template slot, zero the record and retire the
 * widget that was drawn for it.  160 bytes, 40 instructions, 1 branch,
 * 3 calls.
 *
 * * DIRECT NEIGHBOUR of `factory_FactoryMarkerAddFromSavedSlot_4f6d10`, so the container types come
 *   over verbatim: `f78` is `Pt3 *` with `sizeof == 0x14` (`sll 2 / addu /
 *   sll 2` is `(i * 4 + i) * 4`) and `f7C` is the one-record template.
 * * `dsll32 $17, $5, 16 / dsra32 $17, $17, 16` on the PARAMETER is an `s32`
 *   local plus an explicit `(s16)` cast ([[normal-s16-cast-sign-extension]]);
 *   an `s16` local is the measured null.
 * * `bltz $17` branches PAST the body, so the source is the positive `if`,
 *   not an inverted early return.
 * * The scaled index survives all three calls in `$16` while `o->f78` is
 *   RELOADED afterwards -- mwcc CSEs the multiply but never a LOAD across a
 *   call.  Retail computes the tail address ONCE (`lw / addu / sb / sb`), so
 *   the two stores need a SECOND named pointer local; writing them as
 *   `o->f78[i].f0E = 0;` twice is two words long, one `lw`/`addu` pair per
 *   store, and it also flips the `addu`'s operand order to offset-first.
 * * `andi $5, $2, 0xFFFF` after `addiu $2, $17, 0x98` is `func_290010`'s
 *   `u16` id parameter, the spelling `factory_FactoryRemoveDialogLayout_4fbe10` uses.
 */

typedef struct Pt3 {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x2];
    u8  f0E;
    u8  f0F;
    u8  pad10[0x4];
} Pt3;                                          /* 0x14 */

typedef struct Trail {
    u8    pad00[0x78];
    Pt3  *f78;
    void *f7C;
} Trail;

extern void *D_004807F0;                        /* _gp - 0x4980 */

extern void func_1319A8(void *dst, const void *src, s32 n);
extern void func_131B60(void *p, s32 v, s32 n);
extern void func_290010(void *w, u16 id, s32 a, s32 b);

void factory_FactoryMarkerRemoveSlot_4f6e50(Trail *o, s32 n)
{
    s32  i;
    Pt3 *p;
    Pt3 *q;

    i = (s16)n;
    if (i >= 0) {
        p = &o->f78[i];
        func_1319A8(o->f7C, p, 0x14);
        func_131B60(p, 0, 0x14);
        func_290010(D_004807F0, i + 0x98, 0, -1);
        q = &o->f78[i];
        q->f0E = 0;
        q->f0F = 0;
    }
}
