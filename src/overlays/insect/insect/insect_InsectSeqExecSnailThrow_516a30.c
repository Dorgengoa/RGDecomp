#include "types.h"
/* insect 0x00516A30 -- 1,220 bytes, 305 instructions (plus 3 nops of padding).
 *
 * A four-state driver.  The compare chain is 0x3E7, 2, 1, 0 and every arm is
 * entered with a `beql`, so the SOURCE case order is that chain REVERSED --
 * 0, 1, 2, 0x3E7 -- and the arm addresses ascend in exactly that order.
 * Case 0x3E7 is `return 1`; every other path falls out to `return 0`.
 *
 * `(s32)30.0f` is NOT folded: the R5900's `cvt.w.s` is not IEEE, so mwcc
 * emits the conversion at run time; the `sra`/`bgez`/`addiu 1`/`sra` fan
 * after it is a signed divide by two.
 *
 * 0xB0/0xC0/0xD0/0xE0 are SPILL SLOTS (16-byte spaced, below the declared
 * locals), not declared locals -- which is why the declared block 0xF0..0x140
 * still obeys "first declared = highest address, scalars above aggregates".
 * `lh $2, 0xC0($29)` reading one of them is an explicit `(s16)` cast on a
 * spilled s32, the stack-side twin of the `dsll32/dsra32 ..,16` on $23.
 *
 * D_005252E0 is declared as an INCOMPLETE array so it keeps its %hi/%lo pair
 * instead of being handed a gp-relative reloc it cannot reach.
 * _gp is 0x00485170: -0x4C/-0x5C/-0x58/-0x54/-0x50 are 0x00485124/14/18/1C/20
 * and -0x7F74 is D_0047D1FC = PI.
 */

typedef struct Ent {
    u8   pad00[0x41];
    s8   f41;                       /* +0x41 */
    u8   pad42[0x58 - 0x42];
    s32  f58;                       /* +0x58 */
} Ent;

typedef struct Obj {
    u8   pad00[0x4];
    s32  f4;                        /* +0x04 */
} Obj;

typedef struct Ctx {
    u8   pad0000[0x4960];
    u8   f4960[0x5178 - 0x4960];    /* +0x4960 */
    u8   f5178[0x5EF1 - 0x5178];    /* +0x5178 */
    u8   f5EF1;                     /* +0x5EF1 */
} Ctx;

typedef struct Hit {
    void *f00;                      /* +0x00 */
    s32   f04;                      /* +0x04 */
    void *f08;                      /* +0x08 */
} Hit;

typedef struct St {
    f32  f00;                       /* +0x00 */
    f32  f04;                       /* +0x04 */
    f32  f08;                       /* +0x08 */
    f32  f0C;                       /* +0x0C */
} St;

extern u8  D_005252E0[];
extern s32 D_00485124;              /* _gp - 0x4C */
extern f32 D_00485114;              /* _gp - 0x5C */
extern f32 D_00485118;              /* _gp - 0x58 */
extern f32 D_0048511C;              /* _gp - 0x54 */
extern f32 D_00485120;              /* _gp - 0x50 */
extern f32 D_0047D1FC;              /* _gp - 0x7F74, PI */

extern Ctx  *func_31A8D0(void);
extern void  func_148F30(s32 t, St *s);
extern void  func_151080(s32 m, f32 *v);
extern void  func_151110(s32 m, St *s);
extern s32   func_1511F0(s32 h, s32 k);
extern s32   func_151220(s32 h, const u8 *p);
extern void  func_151460(s32 m);
extern void  insect_InsectSeqGetActors_51b7e0(Hit *h, s32 a, s32 b);
extern void  insect_InsectBoardFindPiece_4ee190(void *g, Ent *e, s32 *px, s32 *py);
extern s32   insect_InsectBoardIsInAttackRange_4ee850(void *g, s32 x, s32 y);
extern Ent  *insect_InsectBoardGetPiece_4ee9a0(void *g, s16 x, s16 y);
extern s32   insect_InsectBoardInBounds_4efac0(void *g, s32 x, s32 y);
extern void  insect_InsectBoardCellToWorld_4eda70(void *g, f32 *a, f32 *b, f32 *c, s32 k,
                                 f32 x, f32 y);
extern void  insect_InsectBattleSetFlag_50dad0(Ctx *c, s32 k);
extern s32   insect_InsectBattleGetPieceModel_50df60(Ctx *c, Ent *e);
extern void  insect_InsectBattleApplyDamage_50f350(Ent *a, Ent *b, s32 n, void *d, s32 e);
extern void  insect_InsectBattlePieceSetDesignVisible_50fa80(s32 h, Ent *e, s32 k);
extern s32   insect_InsectBattleSpecialDamage_50fc50(Ent *e, Ent *t, void *d);
extern void  insect_InsectBattlePlayBankSe_5107d0(s32 k);
extern void  insect_InsectPieceSetStatus_5132d0(Ent *e, s32 k);
extern void  insect_InsectPieceClearStatus_513340(Ent *e, s32 k);
extern void  insect_InsectBattleEffectsSpawn_51dc30(void *q, Ent *e, s32 a, s32 b, s32 c,
                                 s32 x, s32 y, s32 k, s32 f);

s32 insect_InsectSeqExecSnailThrow_516a30(Obj *o)
{
    s32   cx;
    s32   cy;
    f32   fa;
    f32   fb;
    f32   fc;
    Hit   st;
    St    st2;
    f32   u[4];
    f32   z[4];
    Ctx  *ctx;
    void *g;
    Ent  *e;
    Ent  *ent;
    void *e0;
    s32   m;
    s32   h;
    s32   t;
    s32   i;
    s32   j;
    s32   bx;
    s32   by;
    s32   a;
    s32   b;
    s32   tx;
    s32   cy2;
    void *q5178;
    s32   k;
    s32   lim;
    s32   nlim;
    f32   d;
    f32   s;
    f32   q;
    f32   r;
    u8   *p;
    u32   n;
    f32   fps;

    fps = 30.0f;
    lim = (s32)fps / 2 - 5;
    nlim = -lim;
    ctx = func_31A8D0();
    q5178 = ctx->f5178;
    g = ctx->f4960;
    insect_InsectSeqGetActors_51b7e0(&st, 2, 1);
    e = (Ent *)st.f00;
    e0 = st.f08;
    insect_InsectBoardFindPiece_4ee190(g, e, &cx, &cy);
    bx = cx;
    by = cy;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            if (insect_InsectBoardIsInAttackRange_4ee850(g, j, i) != 0) {
                bx = j;
                by = i;
                break;
            }
        }
    }
    insect_InsectBoardCellToWorld_4eda70(g, &fa, &fb, &fc, 0, (f32)bx, (f32)by);
    h = insect_InsectBattleGetPieceModel_50df60(ctx, e);
    m = e->f58;
    t = func_1511F0(h, func_151220(h, D_005252E0));
    if (t != 0) {
        func_148F30(t, &st2);
    }
    switch (o->f4) {
    case 0:
        insect_InsectBattleSetFlag_50dad0(ctx, ctx->f5EF1 + 0x4A);
        k = e->f58;
        D_00485124 = nlim;
        D_00485114 = 0.0f;
        D_00485118 = 0.0f;
        D_0048511C = 0.0f;
        D_00485120 = 0.0f;
        func_151460(k);
        func_151110(m, &st2);
        q = (fc - st2.f08) / 30.0f;
        o->f4 = o->f4 + 1;
        D_0048511C = q;
        break;
    case 1:
        D_00485114 += 10.0f;
        if (D_00485114 >= 360.0f) {
            D_00485114 -= 360.0f;
        }
        d = D_0048511C;
        s = D_00485118 + d;
        q = st2.f08 + s;
        D_00485118 = s;
        st2.f08 = q;
        if (d > 0.0f) {
            if (q >= fc) {
                st2.f08 = fc;
            }
        } else if (d < 0.0f) {
            if (q <= fc) {
                st2.f08 = fc;
            }
        }
        k = D_00485124;
        r = (f32)(nlim * nlim - k * k) / 100.0f;
        D_00485124 = k + 1;
        D_00485120 = r;
        st2.f04 = st2.f04 + r;
        func_151110(m, &st2);
        p = (u8 *)u;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        u[0] = D_0047D1FC * D_00485114 / 180.0f;
        func_151080(m, u);
        if (D_00485124 >= lim) {
            o->f4 = o->f4 + 1;
        }
        break;
    case 2:
        insect_InsectBattlePlayBankSe_5107d0(0x23);
        insect_InsectBattleEffectsSpawn_51dc30(q5178, e, 0x20, 6, 0, -1, -1, 1, m);
        for (a = -1; a <= 1; a++) {
            cy2 = by + a;
            for (b = -1; b <= 1; b++) {
                tx = bx + b;
                if (insect_InsectBoardInBounds_4efac0(g, tx, cy2) != 0) {
                    ent = insect_InsectBoardGetPiece_4ee9a0(g, (s16)tx, (s16)cy2);
                    if (ent != 0) {
                        insect_InsectPieceClearStatus_513340(e, 0x10);
                        insect_InsectBattleApplyDamage_50f350(e, ent,
                                            insect_InsectBattleSpecialDamage_50fc50(e, ent, e0),
                                            e0, 0);
                    }
                }
            }
        }
        p = (u8 *)z;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        func_151080(m, z);
        insect_InsectPieceSetStatus_5132d0(e, 0x19);
        e->f41 = 2;
        insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(ctx, e), e, -1);
        o->f4 = 0x3E7;
        break;
    case 0x3E7:
        return 1;
    }
    return 0;
}
