#include "types.h"

/* factory.bin overlay, 0x004F0920 -- build the factory screen's item cursor.
 *
 * 204 instructions, 35 calls, ZERO conditional branches: the straight-line
 * tier.
 *
 * ★ Retail caches the ADDRESS `addiu $16, $2, 0x4` of the sub-object inside
 * the func_28EA40 result and keeps it across eleven calls, which is the
 * pointer-to-sub-object spelling; caching the BASE would have been
 * `daddu $16, $2, $0` (the insmenu offset-folding finding, from the other
 * side).
 *
 * ★ `mtc1 $0,$f0` + `adda.s $f0,$f1` + `madd.s $f0,$f1,$f0` is `K + a * b`:
 * mwcc starts an add containing a product by seeding the accumulator from a
 * zeroed FPR, so the `mtc1 $0` is compiler output and the 32.0f is the source's
 * constant.  `lui 0x4200` materialises it INLINE because its low half is zero.
 *
 * ★ `mult1` is the EE's second multiply pipe -- two independent source-level
 * multiplies, not one special instruction.
 *
 * ⚠⚠ STILL PARKED, now 5 bad (was 7) -- session 17 lane fs07 named the float
 * into `f32 t0 = D_0047D4F4;` read AHEAD of the two `sh $0` stores, which lifts
 * the `lwc1` past those stores' alias hazard ([[factory-gp-load-placement]]) and
 * buys two words.  It now sits at prologue slot 5; retail has it at slot 2,
 * INSIDE the callee-saved `sq` block, and no source form reaches there:
 * `extern const f32` is +1 WORD (wrong length) and initializer-vs-assignment is
 * INERT.  RIGHT LENGTH (201 words),
 * 5 bad, and the residue is a pure ROTATION of the prologue: retail issues
 * `lwc1 $f0, -0x7C7C($28)` as the SECOND instruction, interleaved with the
 * callee-saved `sq`s, and we issue it at its use seven words later.  Nothing
 * else differs.  This is the gp-float-hoist class the overlay track closed as a
 * BOUNDED NEGATIVE in the title session (fifteen spellings across two shapes,
 * byte-for-byte identical objects, and no scheduling knob in `-opt dump` or
 * `-help all`); do not re-open it without a new compiler.
 * ★ Priced in factory: 10 functions issue a gp float load inside the
 * callee-saved save block, 4,756 bytes = 3.56% of the text -- the biggest of
 * them are 004F0920, 004FBAB0 (796 B), 004FB0F0 (728 B) and 00505AF0 (612 B).
 * Skip that list when choosing targets rather than writing them and parking.
 *
 * ⚠ func_290F60 takes FOUR arguments.  m2c gives one site five because the
 * preceding `mult` result is still in $8; read $4..$7 off the reference.
 */

typedef struct Box {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u8  pad8[8];
    s16 f10;
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Box;

typedef struct Item {
    u8  pad0[4];
    Box b;
} Item;

typedef struct Pad {
    s8 f0;
    s8 f1;
} Pad;

typedef struct Scr {
    u8    pad0[0x5C];
    f32   f5C;
    s16   f60;
    s16   f62;
    u8    pad64[8];
    f32   f6C;
    s16   f70;
    u8    pad72[2];
    u8    f74[0x14];
    u8    f88;
    u8    pad89[3];
    void *f8C;
    void *f90;
    u8    pad94[8];
    u8    f9C[0x40];
} Scr;

extern void *D_00484A70;

extern void  factory_FactoryPartsRefreshIcons_4efc80(Scr *o);
extern void  factory_FactoryPartsRefreshDetail_4efd30(Scr *o);
extern void  factory_FactoryPartsListBuild_4efe90(Scr *o);
extern s32   func_1FEDE0(void);
extern void *func_206AE0(void);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D820(void *w, s32 id);
extern void  func_28D9C0(void *w, s32 a);
extern void  func_28D9D0(void *w);
extern void  func_28DA30(void *w, void *ctx, s32 id);
extern void  func_28DAA0(void *w, s32 id, s32 x, s32 y);
extern void  func_28DB40(void *w, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f,
                         s32 g);
extern void  func_28DB70(void *w);
extern Item *func_28EA40(void *ctx, s32 id);
extern void  func_28F510(void *ctx, s32 id, void *p, s32 n);
extern void  func_2907A0(void *ctx, s32 id, f32 t);
extern void  func_290BD0(void *ctx, s32 id, s32 a, s32 b, s32 c, s32 d);
extern void  func_290F60(void *ctx, s32 id, s32 x, s32 y);
extern void  func_40C380(void *w, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f,
                         s32 g);

void factory_FactoryPartsOpen_4f0920(Scr *o)
{
    Item *it;
    Box *b;
    Pad *pad;

    o->f60 = 0;
    o->f62 = 0;
    o->f5C = -3.1415927f;
    func_28DB70(o->f9C);
    func_28DA30(o->f9C, o->f8C, 0x4B);
    func_28DB40(o->f9C, 0x4B, 0x1A, 0x1A, 0x4C, 0x4C, 0, 0);
    func_28D9D0(o->f9C);
    func_28D9C0(o->f9C, 1);
    func_28DAA0(o->f9C, 0x4B, 0x1A, 0x1A);
    func_28D820(o->f9C, 0x4B);

    it = func_28EA40(o->f90, 0x88F4);
    b = &it->b;
    func_290F60(o->f8C, 0x4C, it->b.f0, it->b.f2);
    func_290F60(o->f8C, 0x44, 0, 0);
    func_290BD0(o->f8C, 0x45, 0x200, 1, 0, 0);
    func_28F510(o->f8C, 0x45, func_28AA30(D_00484A70, 0x18), 0);
    func_28F510(o->f8C, 0x45, func_28AA30(D_00484A70, 5), 1);
    func_28F510(o->f8C, 0x45, func_28AA30(D_00484A70, 6), 2);
    func_28F510(o->f8C, 0x45, func_28AA30(D_00484A70, 7), 3);
    func_2907A0(o->f8C, 0x45, 0.0f);
    func_2907A0(o->f8C, 0x46, 0.0f);
    func_290F60(o->f8C, 0x46, -0xE, -0x36);
    func_2907A0(o->f8C, 0x47, 0.0f);
    func_290F60(o->f8C, 0x47, -0xE, -0x36);
    func_40C380(o->f74, func_1FEDE0(), 0x12, -1, 1, 1, 0, 1);

    o->f88 = 0;
    o->f70 = 0;
    o->f6C = 0.0f;
    factory_FactoryPartsListBuild_4efe90(o);
    pad = func_206AE0();
    b->f12 = 0;
    b->f16 = pad->f1;
    factory_FactoryPartsRefreshIcons_4efc80(o);
    b->f12 = pad->f0;
    factory_FactoryPartsRefreshDetail_4efd30(o);

    o->f60 = b->f12;
    o->f62 = b->f16;
    func_290F60(o->f8C, 0x43, 0x6F, (s32)(32.0f + (f32)b->f16 * o->f6C));
    func_290F60(o->f8C, 0x44, 0, b->f12 * b->f6);
    func_290F60(o->f8C, 0x4C, b->f0 + b->f10 * b->f4,
                b->f2 + b->f12 * b->f6);
    func_28DAA0(o->f9C, 0x4B, b->f10 * b->f4 + 0x1A, b->f12 * b->f6 + 0x1A);
    func_28D820(o->f9C, 0x4B);
}
