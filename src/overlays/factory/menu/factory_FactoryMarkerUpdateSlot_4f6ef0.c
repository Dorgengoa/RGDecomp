#include "types.h"

/* factory.bin overlay, 0x004F6EF0 -- 236 bytes / 59 words, 7 branches, 1 call.
 * Rewrite one live trail record from a source vector and re-arm the number
 * widget that belongs to it.
 *
 * * Same container as the byte-identical `factory_FactoryMarkerClearAllSlots_4f6dd0` /
 *   `factory_FactoryMarkerRemoveSlot_4f6e50`: `f78` is the 0x14-stride record array, and
 *   `D_0050BB20` is `factory_FactoryMarkerDrawNumber_4f5710`'s 0x40-stride `Num` table, so both
 *   scalings (`sll 2 / addu / sll 2` and `sll 6`) come over verbatim.
 * * `dsll32/dsra32 ..,16` on the a2 and a3 PARAMETERS is an `s32` parameter
 *   plus an explicit `(s16)` cast ([[normal-s16-cast-sign-extension]]); the a3
 *   cast is emitted THREE times, so it is written three times in source and is
 *   NOT a named local.
 * * `lh $10, 0xC($11)` is hoisted ABOVE the four stores, so the old value must
 *   be a named local read BEFORE them ([[insect-load-across-store]]).  It must
 *   The STATEMENT order is table-pointer first, old-value second (reversing
 *   the two statements is 18 wrong words, worse than 16); what picks the two
 *   temporaries apart is the DECLARATION order -- `old` declared BEFORE `t`
 *   puts `old` in $10 and lets `t` reuse the scaled-index register $9 in
 *   place, which is also what produces retail's interleaved schedule.
 * * `slti $1` into `$at` on the clamp is the STRICT compare -- `> 0x63`, not
 *   `>= 0x64`; `slti $3` into a general register on the 0xA test is the
 *   non-strict `>= 0xA`.
 * * The unconditional `sh $5, 0x0($9)` in the branch delay slot is the DEFAULT
 *   assignment overwritten on one path, not an if/else (an if/else would not
 *   store 0x16 on the 0x1C path).
 * * `daddu $5, $6, $0` at the tail passes the RAW a2, not the `(s16)` cast.
 */

typedef struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    u8  f0E;
    u8  f0F;
    s32 f10;
} Cell;                                         /* 0x14 */

typedef struct Ctx {
    u8    pad00[0x78];
    Cell *f78;
} Ctx;

typedef struct Src {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x4];
    s16 f10;
} Src;

typedef struct Num {
    s16 f00;
    u8  pad02[0x6];
    s64 f08;
    u8  pad10[0x30];
} Num;                                          /* 0x40 */

extern Num D_0050BB20[];

extern void factory_FactoryMarkerSetKindUv_4f61a0(Ctx *o, s32 idx);

void factory_FactoryMarkerUpdateSlot_4f6ef0(Ctx *o, Src *s, s32 idx, s32 v, u8 f)
{
    Cell *e;
    s32   old;
    s32   i;
    Num  *t;

    if (s == 0) {
        return;
    }
    i = (s16)idx;
    if (i < 0) {
        return;
    }
    e = &o->f78[i];
    if (e->f0E == 0) {
        return;
    }
    old = e->f0C;
    e->f00 = s->f00;
    e->f04 = s->f04;
    e->f08 = s->f08;
    e->f0C = s->f10;
    e->f0F = f;
    t = &D_0050BB20[i];
    t->f08 = (s16)v;
    if (t->f08 > 0x63) {
        t->f08 = 0x63;
    }
    t->f00 = 0x16;
    if ((s16)v >= 0xA) {
        t->f00 = 0x1C;
    }
    if (((s16)old != e->f0C) && (e->f0C > 0)) {
        e->f10 = 0;
        factory_FactoryMarkerSetKindUv_4f61a0(o, idx);
    }
}
