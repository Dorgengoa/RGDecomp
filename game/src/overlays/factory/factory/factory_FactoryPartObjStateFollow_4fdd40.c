/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjStateFollow_4fdd40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FDD40 -- re-aim the preview model at the cursor:
 * rebuild its scale when the shape id has changed, then compose the camera's
 * rotation onto it and re-seat it against the world box.
 * 460 bytes, 116 instructions, 3 conditional branches, 17 calls.
 *
 ** `nd = o->f20` is a NAMED LOCAL at the ONE site where a LOOP separates the
 * read from the use -- retail hoists that load above the clear loop and the
 * inline spelling emits it below, shifting fifteen words.  This is the exact
 * shape [[factory-count-the-gp-loads]]'s session-9 note records, on the same
 * callee `func_1865B0`.
 *
 * * `o->f20` is spelled at the other SIX call sites and re-read every time; the
 * shape id `a->f24` likewise at its four.  A call separates each pair, so
 * mwcc's per-basic-block CSE reproduces the reloads for free
 * ([[factory-count-the-gp-loads]]).
 *
 ** `k = D_0047DB50` IS THE LAST FOUR WORDS.  mwcc will not move a gp-relative
 * GLOBAL LOAD above a STORE it cannot disambiguate, so with the constant
 * spelled at the call the `lwc1` lands BELOW `g->f444 = a->f04` and the three
 * words {store, lwc1, daddu $6} rotate through the delay slot.  Naming it in a
 * local BEFORE the store is exact.  [[insect-load-across-store]] in the
 * load-before-store direction.
 * ⚠⚠ Thirteen tail spellings and the whole 19-knob `f_knob.py` surface are a
 * measured NULL on this rotation, and so is moving the float to parameter TWO
 * of `func_1CBB20` -- that one LOOKED like the lever (it matches retail's
 * `f12`-before-`$5` setup order) and was RE-TESTED and reverted once `k`
 * existed.  It is inert.
 *
 * * `lui $2, 0x3F80` + `sw` is `1.0f` stored through the INTEGER file -- mwcc's
 * form for a float constant going straight to memory, not a pool load.
 *
 * * The 0x10-byte clear is the byte loop with the redundant null test and an
 * UNSIGNED counter that `factory_FactoryPartObjGetGridY_4fe0c0` and `factory_FactoryPartGroupBuildObjs_4fead0`
 * already carry.
 *
 * * mwcc allocates stack LOCALS in REVERSE declaration order -- the LAST one
 * declared takes the lowest address.  Retail's `0x40/0x50/0x60/0x70` therefore
 * reads as `u, m, t, s` in the source, and the naive forward order puts every
 * one of the four at the wrong offset for 20 wrong words at the RIGHT LENGTH.
 */

typedef struct Vec {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
} Vec;                                          /* 0x10 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Shape {
    u8  pad00[0x4];
    f32 f04;
    u8  pad08[0x8];
    Vec f10;
    u8  pad20[0x4];
    s32 f24;
} Shape;

typedef struct Prev {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    u8    pad26[0x1];
    s8    f27;
    s16   f28;
} Prev;

typedef struct Cam {
    u8  pad000[0x430];
    f32 f430;
    u8  pad434[0x4];
    f32 f438;
    u8  pad43C[0x4];
    f32 f440;
    f32 f444;
    f32 f448;
    u8  pad44C[0x4];
    f32 f450;
    u8  pad454[0x4];
    f32 f458;
} Cam;

extern f32 D_0047DB50;                          /* _gp - 0x7620 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartObjStateFollow_4fdd40(Prev *o, Shape *a)
{
    Vec  u __attribute__((aligned(16)));
    Vec  m __attribute__((aligned(16)));
    Vec  t __attribute__((aligned(16)));
    Vec  s __attribute__((aligned(16)));
    f32  k;
    Cam *g;
    Node *nd;
    s8  *p;
    u32  n;

    o->f20->f32 = 1;
    if (o->f24 != o->f25) {
        factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, a->f24, 0);
        factory_FactoryPartObjSetFuncFlag_4fd260(o, a->f24, 0);
        factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, a->f24, 0);
        factory_FactoryPartObjSetNodesVisible_4fd110(o, a->f24, 0);
        nd = o->f20;
        p = (s8 *)&s;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        s.f00 = 1.0f;
        s.f04 = 1.0f;
        s.f08 = 1.0f;
        NodeSetScale_1865b0(nd, &s);
        o->f24 = o->f25;
        o->f28 = 0;
    }
    NodeGetRotation_1865e0(o->f20, &m);
    VecSub_1cbd00(&t, &a->f10, &m);
    t.f00 = AngleWrap_1cbf30(t.f00);
    t.f04 = AngleWrap_1cbf30(t.f04);
    t.f08 = AngleWrap_1cbf30(t.f08);
    t.f0C = 0;
    VecScale_1cbca0(&t, &t, D_0047DB50);
    VecAdd_1cbdc0(&m, &m, &t);
    NodeSetRotation_186620(o->f20, &m);
    g = ((Cam *)GetFactoryObj_367f30());
    NodeGetTranslation_186650(o->f20, &u);
    k = D_0047DB50;
    g->f444 = a->f04;
    VecLerp_1cbb20(&u, (Vec *)&g->f440, &u, k);
    u.f00 = g->f440 - (g->f450 - g->f430);
    u.f08 = g->f448 - (g->f458 - g->f438);
    u.f0C = 1.0f;
    NodeSetTranslation_1866b0(o->f20, &u);
    o->f25 = 0;
    o->f27 = 0;
    o->f28 = 0;
}
