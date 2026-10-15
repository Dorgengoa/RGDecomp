#include "types.h"

/* factory.bin overlay, 0x004F1C50 -- 136 bytes / 34 words.  Re-sync the two
 * cached scroll positions of list widget 0x8944 into the module.
 *
 * ★ THE RESIDUE WAS THE STRUCT, NOT THE CODE.  A first draft that read every
 * field off the func_28EA40 result was wrong in exactly five words, and all
 * five were the SAME UNIFORM +4 DISPLACEMENT (`daddu $16,$2,$0` where retail
 * has `addiu $16,$2,0x4`, then 0x0A/0x16/0x1A where retail has 0x06/0x12/0x16)
 * -- the [[insect-struct-overlap-declaration]] tell.  The record carries a
 * 4-byte header and the fields this unit touches live in a SUB-STRUCT at +4
 * that the source names in its own pointer; that pointer is what survives the
 * func_290F60 call in $16.
 *
 * ★ mwcc materialises `s = &r->sub` LAZILY: the first read still comes out as
 * `lh $7, 0x16($2)` off the raw return value and the `addiu $16,$2,4` lands in
 * the beq's delay slot.  Five spellings (n-then-s / s-then-n / no named n /
 * an explicit `(Sub *)((u8 *)r + 4)` cast / everything through s) all produce
 * the IDENTICAL object -- the sub-struct is the whole lever and its
 * placement is inert.
 *
 * * `ori $5,$0,0x8944` rather than `addiu` is just `li` of a value above
 *   0x7FFF; the id parameter stays `s32`, as in factory_FUN_004ED6D0.
 * * `mult $2, $7, $2` is the three-operand EE mult reusing the guard's loaded
 *   field as the left factor, so that field is a NAMED LOCAL.
 * * The second guard is `beql` PAST the body with `ld $31` duplicated into the
 *   likely slot; the join is the epilogue.
 */

typedef struct Sub {
    u8  pad00[0x6];
    s16 f06;
    u8  pad08[0xA];
    s16 f12;
    u8  pad14[0x2];
    s16 f16;
} Sub;

typedef struct Rec {
    u8  pad00[0x4];
    Sub sub;
} Rec;

typedef struct Mod {
    u8    pad00[0x60];
    s32   f60;
    s32   f64;
    u8    pad68[0x20];
    void *f88;
    void *f8C;
} Mod;

extern void factory_FactoryHelpTopicListRefresh_4f1240(Mod *o);
extern Rec *func_28EA40(void *ctx, s32 id);
extern void func_290F60(void *w, s32 id, s32 x, s32 y);

void factory_FactoryHelpSelChanged_4f1c50(Mod *o)
{
    Rec *r;
    Sub *s;
    s32  n;

    r = func_28EA40(o->f8C, 0x8944);
    s = &r->sub;
    n = s->f12;
    if (n != o->f60) {
        func_290F60(o->f88, 0x82, 0x1A, n * s->f06 + 0x3E);
        o->f60 = s->f12;
    }
    if (s->f16 != o->f64) {
        factory_FactoryHelpTopicListRefresh_4f1240(o);
        o->f64 = s->f16;
    }
}
