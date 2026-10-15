/* SESSION 41 (n41f, SOLO): CLOSED -- 800/800 words, 6 bad -> BYTE-IDENTICAL.
 * The whole residue was ONE FPR staircase in the line
 *     w->f40 = (s16)((f32)(w->f00 + w->f04) + 2.0f * tC0[i]);
 * and the fix is ONE TOKEN in the STRUCT, not in that line:
 *     s32 f34;  ->  f32 f34;      (and `w->f34 = 0;` -> `w->f34 = 0.0f;`)
 *
 * WHY.  `x + y*z` is the R5900 accumulator idiom ([[ps2-float-accumulator]]):
 * mwcc materialises the addend into ACC with `mtc1 $0,$fS` + `adda.s` and
 * folds the product in with `madd.s`.  That `mtc1 $0` SEED is a float web like
 * any other and takes its register by CREATION ORDER, highest free first
 * ([[mwcc-fpr-decl-order-highest-first]]).  Retail's creation order in the
 * window is (tC0, seed, 2.0f, cvt) = $f3,$f2,$f1,$f0; ours was
 * (tC0, 2.0f, cvt, seed) = $f3,$f2,$f1,$f0 read onto the wrong values.
 * Session 39 proved you CANNOT reach the seed from that statement's own
 * spelling -- 34 arms, 22 of them the byte-identical same object, and every
 * explicit `0.0f +` seed is CONSTANT-FOLDED AWAY before the vreg exists.
 * The seed's web is reachable from the NEIGHBOURING STATEMENT instead:
 * `w->f34 = 0;` two lines above becomes a FLOAT ZERO once f34 is `f32`, so a
 * zero-float web is created THERE, one statement before the f40 line's
 * operands -- exactly retail's order.  ⚠ The store itself does not change:
 * mwcc still spells a 0.0f store as `sw $0`, so the length is untouched.
 * (`f32 f34;` with the store left as the integer literal `0` is the SAME
 * OBJECT -- the member TYPE is the whole lever.)
 *
 * ⇒ TRANSFERABLE: when a residue is the accumulator seed's register and the
 * statement itself is exhausted, look for a NEIGHBOURING `= 0` store whose
 * member type would make it a float zero.  [[mwcc-float-zero-seed-web]].
 *
 * The session-39 negative record is kept below because it is what proves the
 * statement-local axis was closed, and it is still binding for anyone who
 * reads this line and reaches for another spelling of it.
 *
 * S39 NEGATIVES (all at the pre-close baseline, all still true):
 *   - operand order `2.0f*tC0[i] + X`, `X + tC0[i]*2.0f`, `tC0[i]*2.0f + X`
 *     -- the SAME OBJECT as the base ([[mwcc-commutative-add-operand-order]]
 *     does not bite here).
 *   - an explicit `0.0f +` seed in FOUR placements, including the
 *     parenthesised `(0.0f + X) + 2.0f*t` -- all folded, same object.
 *   - named f32 locals for the cvt value, the tC0[i] CSE, the 2.0f, both, and
 *     the RESULT, each declared first and last -- same object every time.
 *   - `(s16)(s32)` double cast -- same object.
 *   - REGRESSIONS: multiplying `w->f30` instead of `tC0[i]` (27 bad, kills the
 *     CSE); moving `w->f30 = tC0[i];` after the f40 line (29 bad);
 *     `tC0[i] / 0.5f` and `tC0[i] + tC0[i]` (length wrong).
 *   - PRAGMA CHANNEL ARMED (a bogus pragma name reproduced 800/6) AND SPENT:
 *     removing `#pragma optimization_level 3`, levels 2 and 4, opt_propagation
 *     off, opt_common_subs off, peephole off, opt_loop_invariants off and
 *     usefloatacc off ALL CHANGE THE LENGTH; usefloatacc on, scheduling off
 *     and opt_repositioncode off are inert at 6.
 * S41 NEGATIVES (this session, same deck as the close): a named `two = 2.0f;`
 * local is inert (same object); a named `tv = tC0[i];` is 1 word SHORT; a
 * separate `zf = 0.0f;` local is 1 word LONG (and 3 long when volatile-pinned
 * at the access); multiplying `w->f30` is 27 bad; moving the f40 line above
 * `w->f34` or up next to `w->f30` is 28 bad. */
#include "types.h"
#pragma optimization_level 3
/* normal 0x005135F0 -- FRESH in s32 (lane nf32g).  The map screen slot layout
 * pass: six const tables are copied into locals, the eight slot widgets are
 * placed from them, D_00525AF0 nine key/slot pairs are then enabled or greyed
 * by func_3ED680 answer, and finally the cursor is parked (or interpolated
 * between two slots) for the caret at id 0x1F.
 *
 * SIX LOCAL AGGREGATE COPIES.  Every one of the copy loops in the prologue is
 * mwcc inline struct copy: lh/lh/sh/sh unrolled by two with a countdown of
 * bytes/4 for an align-2 array, lw/lw/sw/sw with bytes/8 for the align-4 f32
 * one.  They are spelled here as a STRUCT ASSIGNMENT from an extern const
 * (T160 t160 = D_00525B40;) rather than as a brace initialiser: a brace
 * initialiser makes mwcc emit its OWN template into this object .data, and
 * the scorer cannot resolve a reloc against a symbol defined in this object,
 * so every %hi/%lo pair would read as a bad word even if the instruction were
 * right.
 *
 * STACK LAYOUT MODEL (this draft bet): locals descend from the top of the
 * frame in DECLARATION order and each aggregate is 16-byte aligned.  That
 * predicts t160@0x160, t100@0x100, tE0@0xE0, tC0@0xC0, tA0@0xA0 and t80@0x80
 * -- the 24-byte t80 would land at 0x88 without the 16-alignment, and retail
 * base is 0x80.  The four floats sit ABOVE t160 at 0x1A0-0x1AF and are read
 * at entry before they are written (retail four lwc1 $f20-$f23 from an
 * untouched slot), so they are declared FIRST and uninitialised.
 */

typedef struct Wid {
    s16 f00; s16 f02; s16 f04; s16 f06;
    s16 f08; s16 f0A; s16 f0C; s16 f0E;
    u8  pad10[0x20 - 0x10];
    s16 f20; s16 f22; s16 f24; s16 f26;
    s16 f28; s16 f2A; s16 f2C; s16 f2E;
    f32 f30;
    f32 f34;
    s16 f38; s16 f3A;
    u8  pad3C[4];
    s16 f40; s16 f42; s16 f44; s16 f46;
    s16 f48; s16 f4A; s16 f4C; s16 f4E;
} Wid;

typedef struct Hold { u8 pad00[0x20]; Wid *f20; } Hold;

typedef struct Menu {
    u8  pad00[0x18];
    s32 f18;
    u8  pad1C[0x24 - 0x1C];
    s16 f24[3][4];
    s16 f3C;
    s16 f3E;
    u8  pad40[0x4A - 0x40];
    s16 f4A[3][4];
    u8  pad62[0x68 - 0x62];
    s32 f68;
} Menu;

typedef struct Ent2 {
    u8  pad000[0x1A4];
    u8  f1A4;
    u8  pad1A5[0x1AC - 0x1A5];
    f32 f1AC;
    f32 f1B0;
} Ent2;

typedef struct Ent { u8 pad00[0x10]; void *f10; u8 pad14[4]; Ent2 *f18; } Ent;

typedef struct Key { s16 f00; s16 f02; s16 f04; s16 f06; } Key;

extern Key D_00525AF0[9];

typedef struct T160 { s16 v[8][4]; } T160;
typedef struct T100 { s16 v[8][6]; } T100;
typedef struct TE0  { s16 v[8][2]; } TE0;
typedef struct TC0  { f32 v[8];    } TC0;
typedef struct TA0  { s16 v[8][2]; } TA0;
typedef struct T80  { s16 v[3][4]; } T80;

extern const T160 D_00525B40;
extern const T100 D_00525B80;
extern const TE0  D_00525BE0;
extern const TC0  D_00525C00;
extern const TA0  D_00525C20;
extern const T80  D_00525C40;


extern u16 D_00480680[4];        /* gp - 0x4AF0 */
extern u16 D_00480690[4];        /* gp - 0x4AE0 */
extern u16 D_004806A0[4];        /* gp - 0x4AD0 */
extern f32 D_0047D248;           /* gp - 0x7F28 */

extern Ent  *func_1FEDE0(void);
extern Hold *func_290460(void *p, u16 id);
extern void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);
extern void  func_2907A0(void *w, u16 id, f32 v);
extern s32   func_3ED680(void *p, s16 a);
extern s32   func_3CCD70(void *h, s32 id);
extern s32   func_3CCAC0(void *h, s32 id);
extern s32   normal_SpaceMenuGetPrevAreaId_514780(void);
extern s32   normal_SpaceMenuGetTransitToAreaId_5147c0(void);
extern s32   normal_SpaceMenuGetTransitFromAreaId_514800(void);
extern s32   normal_SpaceMenuGetCurrentAreaId_514840(void);

s32 normal_SpaceMenuMapBuild_5135f0(Menu *a)
{
    f32 pp[4];
    s16 t160[8][4];
    s16 t100[8][6];
    s16 tE0[8][2];
    f32 tC0[8];
    s16 tA0[8][2];
    s16 t80[3][4];
    Ent *ent;
    Wid *w;
    Wid *r;
    s32  i;
    s32  k;
    s32  j;
    s32  n;
    s32  d;
    s32  p;
    s32  v;
    s32  sel;
    s32  cur;
    s32  tgt;
    s16  v0;
    s16  v1;

    *(T160 *)t160 = D_00525B40;
    *(T100 *)t100 = D_00525B80;
    *(TE0 *)tE0 = D_00525BE0;
    *(TC0 *)tC0 = D_00525C00;
    *(TA0 *)tA0 = D_00525C20;
    *(T80 *)t80 = D_00525C40;

    ent = func_1FEDE0();

    for (k = 0; k < 3; k++) {
        for (j = 0; j < 4; j++) {
            a->f4A[k][j] = t80[k][j];
        }
    }

    for (i = 0; i < 8; i++) {
        w = func_290460(a, D_00480680[i])->f20;
        v0 = t100[i][0];
        w->f00 = (s16)(v0 - 0xA);
        if (w->f00 == -1) {
            w->f00 = 0;
        }
        v1 = t100[i][1];
        w->f02 = (s16)(v1 - 6);
        w->f20 = (s16)(w->f00 + w->f04);
        w->f22 = w->f02;
        w->f30 = tC0[i];
        w->f34 = 0.0f;
        w->f38 = 2;
        w->f3A = 0xC;
        w->f40 = (s16)((f32)(w->f00 + w->f04) + 2.0f * tC0[i]);
        w->f42 = w->f02;

        r = func_290460(a, D_00480690[i])->f20;
        r->f08 = t160[i][0];
        r->f0A = t160[i][1];
        r->f04 = r->f0C = t160[i][2];
        r->f06 = r->f0E = t160[i][3];

        if (i == 6) {
            r = func_290460(a, 0x1D)->f20;
            r->f00 = v0;
            r->f02 = v1;
            r->f08 = t100[i][2];
            r->f0A = t100[i][3];
            r->f04 = r->f0C = t100[i][4];
            r->f06 = r->f0E = t100[i][5];
        } else {
            r->f20 = v0;
            r->f22 = v1;
            r->f28 = t100[i][2];
            r->f2A = t100[i][3];
            r->f24 = r->f2C = t100[i][4];
            r->f26 = r->f2E = t100[i][5];
        }

        if (i == 2) {
            r->f40 = 0x31;
            r->f42 = 0x38;
            r->f48 = 0xEC;
            r->f4A = 0xC2;
            r->f44 = r->f4C = 0x10;
            r->f46 = r->f4E = 0x10;
        } else if (i == 4) {
            func_290F60(a, 6, 0, 0x5D);
            func_291110(a, 6, 1, 1);
            func_290F60(a, 5, 0x6F, 0xAF);
            func_291110(a, 5, 1, 1);
        }

        func_290F60(a, D_004806A0[i], tE0[i][0], tE0[i][1]);
        func_291110(a, D_004806A0[i], 1, 1);
    }

    func_2907A0(a, 0x1C, D_0047D248);

    for (n = 0; n < 9; n++) {
        if (D_00525AF0[n].f00 == 9) {
            continue;
        }
        v = func_3ED680(ent, D_00525AF0[n].f00);
        if (v == 0) {
            func_291110(a, D_004806A0[D_00525AF0[n].f02], 0, 1);
            if (D_00525AF0[n].f00 == 6) {
                func_291110(a, 5, 0, 1);
                func_291110(a, 6, 0, 1);
            }
            for (k = 0; k < 3; k++) {
                for (j = 0; j < 4; j++) {
                    if (t80[k][j] == D_00525AF0[n].f00) {
                        t80[k][j] = -1;
                    }
                }
            }
        } else if (v == 1) {
            func_291110(a, D_00480680[D_00525AF0[n].f02], 0, 1);
            if (D_00525AF0[n].f02 == 6) {
                func_291110(a, 0x1D, 0, 1);
            }
            func_291110(a, D_00480690[D_00525AF0[n].f02], 1, 1);
            r = func_290460(a, D_00480690[D_00525AF0[n].f02])->f20;
            r->f24 = r->f2C = 0;
            r->f26 = r->f2E = 0;
            if (n == 2) {
                r->f20 = 0x31;
                r->f22 = 0x38;
                r->f28 = 0xEC;
                r->f2A = 0xC2;
                r->f24 = r->f2C = 0x10;
                r->f26 = r->f2E = 0x10;
            }
            for (k = 0; k < 3; k++) {
                for (j = 0; j < 4; j++) {
                    if (t80[k][j] == D_00525AF0[n].f00) {
                        t80[k][j] = -1;
                    }
                }
            }
        } else {
            func_291110(a, D_00480680[D_00525AF0[n].f02], 1, 1);
            if (D_00525AF0[n].f02 == 6) {
                func_291110(a, 0x1D, 1, 1);
            }
            r = func_290460(a, D_00480690[D_00525AF0[n].f02])->f20;
            r->f08 = t160[D_00525AF0[n].f02][0];
            r->f0A = t160[D_00525AF0[n].f02][1];
            r->f04 = r->f0C = t160[D_00525AF0[n].f02][2];
            r->f06 = r->f0E = t160[D_00525AF0[n].f02][3];
        }
    }

    for (k = 0; k < 3; k++) {
        for (j = 0; j < 4; j++) {
            a->f24[k][j] = t80[k][j];
        }
    }

    sel = normal_SpaceMenuGetCurrentAreaId_514840();
    if (sel == 9) {
        a->f18 = sel = normal_SpaceMenuGetPrevAreaId_514780();
        if (ent->f18->f1A4 & 1) {
            if (normal_SpaceMenuGetTransitFromAreaId_514800() == 9) {
                a->f18 = sel = normal_SpaceMenuGetPrevAreaId_514780();
            }
        }
    }
    a->f18 = sel;
    if (sel == -1) {
        return 2;
    }

    a->f3C = -1;
    a->f3E = -1;
    for (k = 0; k < 3; k++) {
        for (j = 0; j < 4; j++) {
            if (a->f4A[k][j] == sel) {
                a->f3C = (s16)j;
                a->f3E = (s16)k;
                break;
            }
        }
    }

    a->f68 = 0;
    for (i = 0; i < 9; i++) {
        if (sel == D_00525AF0[i].f00) {
            func_290F60(a, 0x1F, tA0[D_00525AF0[i].f02][0],
                        tA0[D_00525AF0[i].f02][1]);
            func_291110(a, 0x1F, 1, 1);
        }
    }

    if (a->f3C == -1 && a->f3E == -1) {
        for (d = 0; d < 9; d++) {
            p = 0;
            do {
                if (d == D_00525AF0[p].f06 &&
                    (func_3CCD70(ent->f10, D_00525AF0[p].f04) != 0 ||
                     (D_00525AF0[p].f00 == 0x15 &&
                      func_3CCAC0(ent->f10, 2) > 0))) {
                    for (k = 0; k < 3; k++) {
                        Key *e;
                        j = 0;
                        e = &D_00525AF0[p];
                        for (; j < 4; j++) {
                            if (a->f4A[k][j] == e->f00) {
                                a->f3C = (s16)j;
                                a->f3E = (s16)k;
                                func_290F60(a, 0x1F,
                                            tA0[e->f02][0],
                                            tA0[e->f02][1]);
                                func_291110(a, 0x1F, 1, 1);
                                p = 0xFFFF;
                                break;
                            }
                        }
                    }
                }
                p++;
            } while (p < 9);
            if (!(p < 0xFFFF)) {
                break;
            }
        }
    }

    if (ent->f18->f1A4 & 1) {
        cur = normal_SpaceMenuGetTransitFromAreaId_514800();
        tgt = normal_SpaceMenuGetTransitToAreaId_5147c0();
        if (cur == 9) {
            cur = normal_SpaceMenuGetPrevAreaId_514780();
        }
        for (i = 0; i < 9; i++) {
            if (cur == D_00525AF0[i].f00) {
                s16 *q = tA0[D_00525AF0[i].f02];
                pp[2] = (f32)q[0];
                pp[3] = (f32)q[1];
            }
            if (tgt == D_00525AF0[i].f00) {
                s16 *q = tA0[D_00525AF0[i].f02];
                pp[0] = (f32)q[0];
                pp[1] = (f32)q[1];
            }
        }
        {
            {
                f32 tt = ent->f18->f1AC;
                f32 uu = ent->f18->f1B0;
                f32 el;
                pp[0] = (pp[0] - pp[2]) / tt;
                pp[1] = (pp[1] - pp[3]) / tt;
                el = tt - uu;
                pp[0] = pp[0] * el;
                pp[1] = pp[1] * el;
            }
            func_290F60(a, 0x1F, (s32)(pp[2] + pp[0]), (s32)(pp[3] + pp[1]));
        }
        goto tail;
    }

    if (normal_SpaceMenuGetCurrentAreaId_514840() == 9) {
        a->f18 = sel = normal_SpaceMenuGetPrevAreaId_514780();
        for (i = 0; i < 9; i++) {
            if (sel == D_00525AF0[i].f00) {
                func_290F60(a, 0x1F, tA0[D_00525AF0[i].f02][0],
                            tA0[D_00525AF0[i].f02][1]);
                func_291110(a, 0x1F, 1, 1);
            }
        }
    }
tail:
    return 0;
}
