#include "types.h"

/* factory.bin overlay, 0x004F5E70 -- stroke the one- or two-part connector
 * frame for a blueprint cell.  744 bytes, 188 instructions, 7 conditional
 * branches, 26 calls (br/ins 0.037): the branch-light band.
 *
 * The third member of the factory_FactoryMarkerDrawItemIcon_4f5490 / factory_FactoryMarkerDrawKindAnim_4f51a0 family
 * (0.822 / 0.830 by mnemonic sequence): the same context/scissor preamble and
 * the same two-corner stroke, run twice over a 32-byte table.
 *
 * Relocation notes: D_0050CBF8 and D_0050B500 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so both are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_004807F0 (_gp - 0x4980) is inside
 * the window and stays plain.
 *
 * ★ `slti $2, $20, 0x2` lands in a GPR, so the latch token is `j < 2`; the
 * sibling's `$at` compare is the `> 3` form ([[at-compare-class]]).
 *
 * ⚠⚠ PARKED, session 8 -- RIGHT LENGTH (186 words), 14 bad, and NOT in
 * config/ocunits/factory.txt.  The residue is ONE PAIR SWAP of two
 * callee-saved chains, everything else byte-identical:
 *     retail  idx -> $16 (then `t` in the loop),  r -> $18 (then `y0`)
 *     ours    r   -> $16 (then `t`),              idx -> $18 (then `y0`)
 * The live ranges are IDENTICAL in both builds -- only the names differ -- and
 * the whole loop body from 0x004F6050 on is already byte-identical, so the
 * bad words are the 8 pre-loop references plus the 5-instruction schedule
 * shuffle they drag around the `base` computation.
 * Measured and NOT the answer, 24 spellings over three probe builds:
 *   - eight declaration orders of the seven pointer locals (all 14);
 *   - eight declaration orders of the loop locals (five 14, two WORSE at 22
 *     and 25 -- so declaration order DOES reach this function, it just does
 *     not reach this pair);
 *   - a local copy `i = idx`, `o->f78 + idx` instead of `&o->f78[idx]`,
 *     `base + j` instead of `&base[j]`, and a comma-expression that assigns
 *     `h` inside the func_159FB0 argument list (all 14);
 *   - moving the `skip` early-return to the top, computing `e` before it, and
 *     computing `base` early are all one word SHORT, so they are refuted by
 *     length rather than by bytes.
 * ⇒ [[factory-declaration-order-works]] says a PAIR is one declaration-order
 * build.  It is not reachable here because one member of the pair is a
 * PARAMETER, and no local declaration can order it against `r`.
 *
 * MEASURED INERT, session 23 (lane fz23c), BOTH BYTE-IDENTICAL to the parked
 * object -- do not re-run either:
 *   - a local `s32 i;` declared FIRST and assigned `i = idx;` as the very first
 *     statement, with every use of `idx` rewritten to `i` (mwcc copy-propagates
 *     the local away completely);
 *   - `Ref *r;` moved to the END of the declaration list, after `s32 y1;`.
 * The pair really is idx/r for $16/$18: retail's three parameter homes take
 * $19/$17/$16 in PARAMETER ORDER (o, skip, idx) leaving $18 for `r`; ours take
 * $19/$18/$17 in the order o, idx, skip, leaving $16 for `r`.  The next lever to
 * try is whatever changes the ORDER of the three parameter home copies.
 *
 * ★★ SESSION 23 (lane fz23i): **CLOSED, BYTE-IDENTICAL, 186 words.**
 * The whole 14-word residue -- the $16/$18 chain swap AND the 5-word schedule
 * shuffle around `base` -- was bought by ONE line: hoisting the loop counter
 * clear out of the `for` header so it is a STATEMENT OF ITS OWN placed BEFORE
 * the `base` computation:
 *     j = 0;
 *     base = &D_0050B500[idx * 3];
 *     for (; j < 2; j++) {
 * Retail issues `daddu $20,$0,$0` at 0x004F6034+4, INSIDE the base address
 * arithmetic; ours issued it after.  Giving the clear its own statement ahead
 * of `base` makes its web BORN FIRST, and that one birth-order change flips the
 * whole idx/r colouring cycle ($16={idx,t}, $18={r,y0}) onto retail's.
 * ⇒ THE LESSON: 26 spellings of the DECLARATION list, of the pointer locals and
 * of the parameter homes were all measured INERT on this pair over three earlier
 * sessions.  The pair was never reachable from the DECLARATIONS -- it was
 * reachable from the STATEMENT ORDER of a loop-induction clear that no
 * declaration permutation can move, because a `for` header hides it.
 * HOIST EVERY `for (x = 0; ...)` INIT INTO ITS OWN STATEMENT AND RE-PRICE IT.
 *
 * ★ `base` is spilled with `sq`/`lq` to 0xA0: mwcc's own slot for the loop
 * cursor, below the three declared 16-byte locals.
 */

typedef struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x2];
    u8  f0E;
    u8  f0F;
    u8  pad10[0x4];
} Cell;                                         /* 0x14 */

typedef struct Panel {
    u8    pad00[0x78];
    Cell *f78;
} Panel;

typedef struct Tile {
    s16 f00;
    s16 f02;
    u8  pad04[0x4];
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x10];
} Tile;                                         /* 0x20 */

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;
typedef struct Pos { s32 x; s32 y; s32 z; s32 w; } Pos;
typedef struct Col { f32 r; f32 g; f32 b; f32 a; } Col;

typedef struct Ref  { s16 f00; } Ref;
typedef struct Slot { u8 pad00[0x3C]; f32 f3C; } Slot;

extern void *D_004807F0;                        /* _gp - 0x4980 */
extern u8    D_0050CBF8[];
extern Tile  D_0050B500[];

extern void *func_15DE80(void);
extern void *func_15DE40(void);
extern Ref  *func_159FB0(void *ctx, void *name, s32 k);
extern void  func_1418C0(void *ctx, s16 k, f32 v);
extern s32   func_15D340(Pos *out, Vec *v);
extern Slot *func_290460(void *w, u16 id);
extern void *func_141B00(void *h);
extern void  func_141A20(void *h);
extern void  func_13E500(void *g, s32 a);
extern void  func_13E4F0(void *g, s32 a);
extern void  func_13E4D0(void *g, s32 a);
extern void  func_13E4C0(void *g, s32 a, s32 b);
extern void  func_13E430(void *g, s32 a);
extern void  func_13E3D0(void *g, s32 a);
extern void  func_13E400(void *g, s32 a);
extern void  func_13E460(void *g, s32 a);
extern void  func_13E2F0(void *g, s32 a);
extern void  func_13F730(void *g, s32 a);
extern void  func_13EC00(void *g, void *p);
extern void  func_13EDD0(void *g, Col *c);
extern void  func_13ED60(void *g, s32 a, s32 b);
extern void  func_13EF10(void *g, s32 a, s32 b, s32 c);
extern void  func_13F5B0(void *g);

void factory_FactoryMarkerDrawBase_4f5e70(Panel *o, s32 skip, s32 idx)
{
    Pos   p;
    Vec   v;
    Col   c;
    void *h;
    void *g;
    Ref  *r;
    Slot *s;
    Cell *e;
    Tile *base;
    Tile *t;
    s32   j;
    s32   x0;
    s32   x1;
    s32   y0;
    s32   y1;

    h = func_15DE80();
    r = func_159FB0(func_15DE40(), D_0050CBF8, -1);
    if (r != 0) {
        func_1418C0(func_15DE80(), r->f00, 1.0f);
    }
    if (skip != 0) {
        return;
    }
    e = &o->f78[idx];
    if (e->f0E == 0) {
        return;
    }
    v.x = e->f00;
    v.y = e->f04;
    v.z = e->f08;
    v.w = 1.0f;
    if (func_15D340(&p, &v) == 0) {
        return;
    }
    p.x = p.x - 0x260;
    p.y = p.y - 0x640;
    s = func_290460(D_004807F0, idx + 0x98);
    c.r = 128.0f;
    c.g = 128.0f;
    c.b = 128.0f;
    c.a = 128.0f * s->f3C;
    g = func_141B00(h);
    func_13E500(g, 1);
    func_13E4F0(g, 1);
    func_13E4D0(g, 1);
    func_13E4C0(g, 5, 0);
    func_13E430(g, 1);
    func_13E3D0(g, 1);
    func_13E400(g, 1);
    func_13E460(g, 0);
    func_13E2F0(g, 1);
    func_13F730(g, 6);
    func_13EC00(g, r);
    func_13EDD0(g, &c);
    j = 0;
    base = &D_0050B500[idx * 3];
    for (; j < 2; j++) {
        if (j == 1 && e->f0F == 0) {
            continue;
        }
        t = &base[j];
        x0 = p.x + t->f00 * 16;
        x1 = x0 + t->f0C * 16;
        y0 = p.y + t->f02 * 16;
        y1 = y0 + t->f0E * 16;
        func_13ED60(g, t->f08, t->f0A);
        func_13EF10(g, x0, y0, 0);
        func_13ED60(g, t->f08 + t->f0C, t->f0A + t->f0E);
        func_13EF10(g, x1, y1, 0);
    }
    func_13F5B0(g);
    func_141A20(h);
}
