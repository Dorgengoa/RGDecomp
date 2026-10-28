/* rgp:protos */
#define RGP_SELF_ArenaAllocAligned_370330 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: dense s64 arithmetic with two constant divisions (needs
 * divbyzerocheck pragma) mixed with 32/64-bit sign-extension casts on
 * every intermediate; 0 round trips spent. Needs asm/matchings/main
 * /ArenaAllocAligned_370330.s read by hand to pin which values are genuinely s64 vs
 * m2c over-widening a s32. Not attempted. */
/* s49m: MATCH */
#pragma opt_propagation off
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    u8 pad0[0x2C];
    s32 m2C;
    u8 pad30[4];
    s32 m34;
} Heap;

typedef struct {
    Heap *heap;
    u32 cur;
    s32 used;
} Ctx;

/*rgp*/

u32 ArenaAllocAligned_370330(Ctx *c, s32 size, s32 align, s32 align2)
{
    s64 r;
    Heap *h;
    s32 r1;
    s64 al;
    u32 cur;
    s32 end;
    s32 r2;
    s32 t;
    s32 a;
    s32 blocks;
    s32 n;
    s32 q;
    s64 pad;

    h = c->heap;
    if (h == 0) {
        return 0;
    }
    a = align;
    if (a <= 0) {
        a = 1;
    }
    if (align2 == 0) {
        align2 = 1;
    }
    if (align2 < 0) {
        align2 = a;
    }
    al = align2;
    cur = c->cur;
    r = ModDi3_139820(cur, al);
    pad = 0;
    if (r > 0) {
        pad = al - r;
    }
    r1 = size % a > 0;
    q = size / a;
    n = (q + r1) * a;
    t = pad + n;
    end = c->used + t;
    r2 = end % 16 > 0;
    blocks = end / 16 + r2;
    if (h->m34 - h->m2C < blocks) {
        return 0;
    }
    cur = cur + (s32)pad;
    c->cur += t;
    c->used += t;
    return cur;
}
