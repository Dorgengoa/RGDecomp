#include "types.h"

/* factory.bin overlay, 0x005002C0 -- re-seat the four held pieces: for each one
 * still holding a slot, re-resolve its cell and either create its ghost or move
 * the one it already has.
 * 232 bytes, 60 instructions, 4 conditional branches, 5 calls.
 *
 * * `D_0045B080` is the MAIN-image float `factory_FactoryFloorBuild_503910` already names;
 * `const` is what puts it behind `%hi`/`%lo` instead of `$gp`.  It is spelled
 * INSIDE the loop and -O4 hoists it into `$f20` -- the `lui $3, 0x46` at the
 * top of the function is the hoisted half.
 *
 ** `f08` is `volatile`.  It is read for the sign test and read AGAIN in the
 * else arm's argument -- two `lh $?, 0x8($17)` in adjacent words -- and mwcc
 * CSEs the pair away for every non-volatile spelling.  Twenty-five spellings
 * were measured against this one word: both guard polarities, `<= -1` and
 * `0 >`, a named local for the test or the argument, the `o->f0E0[i]` index
 * form throughout and in each arm separately, a second (unused) parameter on
 * `004EA1A0`, an `s16` return on it, and the callee-parameter signedness sweep
 * `s32/s16/u16/u8/u32/s64/u64` -- of which only the NARROWING types reach the
 * right length, and they buy the reload as an `andi` and not an `lh`.
 * [[insect-volatile-one-of-a-pair]] read from the factory side.
 *
 * * Both skips are `continue`: the outer one is a `bltzl` whose delay slot
 * carries its OWN copy of the counter increment, the inner one a plain `beqz`
 * to the shared one.
 */

typedef struct Held {
    u8  pad00[0x4];
    s16 f04;
    u8  pad06[0x2];
    volatile s16 f08;
    s16 f0A;
    s16 f0C;
    u8  pad0E[0x4];
    s16 f12;
    u8  pad14[0x1C];
    s16 f30;
    u8  pad32[0xE];
} Held;                                         /* 0x40 */

typedef struct Panel {
    u8   pad000[0xE0];
    Held f0E0[4];
} Panel;

typedef struct Req {
    f32 f00;
    f32 f04;
    f32 f08;
    s32 f0C;
    s16 f10;
    u8  pad12[0x2];
} Req;                                          /* 0x14 */

extern const f32 D_0045B080;

extern void *factory_FactoryGridCellAt_5037f0(Panel *o, s32 x, s32 y);
extern f32   factory_FactoryGridCellCenterX_503760(Panel *o, s32 i);
extern f32   factory_FactoryGridCellCenterZ_503730(Panel *o, s32 i);
extern s32   factory_FactoryMarkerAdd_4ea1a0(Req *r);
extern void  factory_FactoryMarkerUpdate_4ea160(Req *r, s32 id, s32 a, s32 b);

void factory_FactorySlotMarkersRefresh_5002c0(Panel *o)
{
    Req   r;
    Held *p;
    s32   i;

    p = o->f0E0;
    for (i = 0; i < 4; i++, p++) {
        if (p->f04 < 0) {
            continue;
        }
        p->f12 = -1;
        p->f30 = 0;
        if (factory_FactoryGridCellAt_5037f0(o, p->f0A, p->f0C) == 0) {
            continue;
        }
        r.f00 = factory_FactoryGridCellCenterX_503760(o, p->f0A);
        r.f04 = D_0045B080;
        r.f08 = factory_FactoryGridCellCenterZ_503730(o, p->f0C);
        r.f0C = p->f04;
        r.f10 = p->f30;
        if (p->f08 < 0) {
            p->f08 = factory_FactoryMarkerAdd_4ea1a0(&r);
        } else {
            factory_FactoryMarkerUpdate_4ea160(&r, p->f08, 0, 0);
        }
    }
}
