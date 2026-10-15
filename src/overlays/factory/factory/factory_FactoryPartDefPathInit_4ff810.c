#include "types.h"

/* factory.bin overlay, 0x004FF810 -- fill in one layout descriptor.
 *
 * ⚠ NINE parameters: `$4`..`$11` plus one word at 0x90($29), which is the
 * caller's first stack argument slot for a frame of 0x90.  Retail reads it with
 * `lw` and stores it with `sh`, so it is an `s32` argument written into an `s16`
 * field, not an `s16` argument.
 * ★ The latch `slt $4, $3, $4` lands in a GPR, not `$at` -- a strict `<` with
 * the induction variable on the LEFT, exactly as [[at-compare-class]] predicts.
 * Spelling it `i <= n - 1` would emit the same instruction into `$at`.
 * ★ `o->f0C` is an array of 6-byte records: `(i*2 + i)*2` is mwcc's strength
 * reduction of `i * 6`, so the index is a real array subscript.
 *
 * ★★ UN-PARKED session 17 (lane fs07): MATCH.  The whole 7-word $4/$5 swap
 * was the COMPOUND ASSIGN.  `o->f12 = o->f12 + o->f0C[i].f04;` loads the
 * accumulator FIRST and gives it $4; `o->f12 += o->f0C[i].f04;` evaluates the
 * RHS first, so the array base takes $4 and the accumulator plus the
 * strength-reduction temp take $5, which is retail.  The earlier six body
 * spellings all kept the `a = a + b` form, so the axis was never crossed.
 * => `+=` is an EVALUATION-ORDER lever, not only a constant-folding one.
 */

typedef struct Elem {
    u8  pad00[0x4];
    s16 f04;
} Elem;                                         /* 6 */

typedef struct Rec {
    s16   f00;
    s16   f02;
    u16   f04;
    s16   f06;
    s16   f08;
    u16   f0A;
    Elem *f0C;
    s16   f10;
    s16   f12;
} Rec;

extern void factory_FactoryPartDefPathReset_4ff910(void);

void factory_FactoryPartDefPathInit_4ff810(Rec *o, s16 a, s16 b, s32 c, s16 d, s16 e, s32 f,
                          Elem *tbl, s32 n)
{
    s32 i;

    factory_FactoryPartDefPathReset_4ff910();
    o->f00 = a;
    o->f02 = b;
    o->f04 = ((o->f04 & ~3) | c) & 3;
    o->f06 = d;
    o->f08 = e;
    o->f0A = ((o->f0A & ~3) | f) & 3;
    o->f0C = tbl;
    o->f10 = n;
    o->f12 = 0;
    for (i = 0; i < o->f10; i++) {
        o->f12 += o->f0C[i].f04;
    }
}
