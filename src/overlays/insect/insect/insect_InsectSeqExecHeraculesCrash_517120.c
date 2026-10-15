/* BYTE-IDENTICAL -- insect session 34 (ix34).  From the ix24 park (2 bad):
 * the two float stores in case 4 are written b->fD8 LAST, with the gp
 * accumulate split into a named local (`v = D_00485104; v += D_00481038;`)
 * and both gp objects declared `const` so the stores cannot alias the
 * stack.  103 arms / 17 distinct objects; four spellings give this object.
 */
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x00517120 -- 1428 bytes, 357 instructions, 23 branches.
 * The six-state driver for a ranged/thrown attack: state 0 rolls the hit,
 * 1 launches, 2 steps the projectile a cell at a time, 3 lands it, 4 runs the
 * flinch timer and 5 finishes.  The jump table jtbl_005252F0 is dense 0..5 but
 * the ARM ADDRESSES put the source order at 0, 1, 3, 4, 5, 2
 * (levers.d/m2c-switch-arm-order).
 *
 * Carries retail's divide-by-zero trap twice, so it needs
 * `#pragma divbyzerocheck on` (levers.d/mwcc-divbyzerocheck-pragma).  Note the
 * two `/` sites are guarded and there is no `%` site here.
 *
 * The state lives in eight _gp-window globals; D_00485110 is the s16 damage
 * latch and D_00485108/D_0048510C the s8 cell the projectile currently
 * occupies.
 */

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x5C - 0x19];
    s32 f5C;                        /* +0x5C */
    u8  pad60[0xD8 - 0x60];
    f32 fD8;                        /* +0xD8 */
} Ent;

typedef struct Ctx {
    u8 pad0000[0x4960];
    u8 f4960[0x506C - 0x4960];      /* +0x4960 */
    u8 f506C[0x5080 - 0x506C];      /* +0x506C */
    u8 f5080[0x5178 - 0x5080];      /* +0x5080 */
    u8 f5178[0x5F82 - 0x5178];      /* +0x5178 */
    u8 f5F82[4];                    /* +0x5F82 */
} Ctx;

typedef struct Ctl {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
} Ctl;

typedef struct Hit {
    Ent *f00;                       /* +0x00 */
    Ent *f04;                       /* +0x04 */
    s32  f08;                       /* +0x08 */
} Hit;

extern s8  D_00485108;              /* _gp - 0x68 */
extern s8  D_0048510C;              /* _gp - 0x64 */
extern s16 D_00485110;              /* _gp - 0x60 */
extern s32 D_00485100;              /* _gp - 0x70 */
extern const f32 D_00485104 __attribute__((section(".sbss")));              /* _gp - 0x6C */
extern const f32 D_00481038 __attribute__((section(".sbss")));              /* _gp - 0x4138 */
extern f32 D_0047DD48;              /* _gp - 0x7428 */
extern f32 D_0047DD20;              /* _gp - 0x7450 */

extern Ctx *func_31A8D0(void);
extern void func_1343B8(void *dst, const char *fmt, ...);
extern s32  func_12DE98(s32 v);

extern void insect_InsectSeqGetActors_51b7e0(Hit *h, s32 a, s32 b);
extern s32  insect_InsectBoardFindPiece_4ee190(void *g, Ent *e, s32 *px, s32 *py);
extern s16  insect_InsectBattleSpecialDamage_50fc50(Ent *a, Ent *b, s32 n);
extern s32  insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern const char *insect_InsectMsgGet_512b70(void *p, s32 k);
extern void insect_InsectBattleDamagePopupSpawn_50f730(Ent *e, s32 a, s32 b);
extern void insect_InsectPlaySe_510870(s32 k);
extern void insect_InsectBattleLogPush_51c2f0(void *p, const char *t, s32 a, s32 b, s32 c);
extern s32  insect_InsectBoardInBounds_4efac0(void *g, s8 x, s8 y);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(void *g, s16 x, s16 y);
extern s32  insect_InsectPieceGetStat_512e20(Ent *e, s32 a, s32 b);
extern s32  insect_InsectPieceRollVsResist_512bf0(Ent *e, s32 a, s32 b);
extern void insect_InsectBoardCellToWorld_4eda70(void *g, f32 *x, f32 *y, f32 *z, s32 k,
                                f32 cx, f32 cy);
extern void insect_InsectPieceMoveTo_5157d0(Ent *e, s32 k, f32 x, f32 y, f32 z, f32 w);
extern void insect_InsectBattleEffectsSpawn_51dc30(void *p, Ent *e, s32 a, s32 b, s32 c, s32 d,
                                s32 f, s32 h, s64 i);
extern void insect_InsectBattleApplyDamage_50f350(Ent *a, Ent *b, s32 n, s32 d, s32 e);
extern void insect_InsectBattlePieceResetMotion_50f960(Ent *e);
extern void insect_InsectBoardTakeAt_4ef770(void *g, s16 x, s16 y);
extern void insect_InsectBoardPlacePiece_4ef830(void *g, Ent *e, s16 x, s16 y);
extern s32  insect_InsectBoardIsHole_4ee7e0(void *g, s32 x, s32 y);
extern s32  insect_InsectPieceIsMoveDone_514a20(Ent *e, s32 a, s32 b);
extern void insect_InsectPieceSetHp_512ee0(Ent *e, s32 k);
extern void insect_InsectBoardHoleClear_4ee780(void *g, s32 x, s32 y);
extern s32  insect_InsectPieceIsInPlay_5149e0(Ent *e);
extern s32  insect_InsectPieceIsEnemyOf_5149b0(Ent *a, Ent *b);

s32 insect_InsectSeqExecHeraculesCrash_517120(Ctl *c)
{
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    f32 px;
    f32 py;
    f32 pz;
    s32 qx;
    s32 qy;
    s32 rx;
    s32 ry;
    Hit hit;
    Ctx *g;
    Ent *b;
    void *p506C;
    void *p5080;
    void *p5178;
    Ent *a;
    void *grid;
    s32 n;
    s32 lx;
    s32 ly;
    s32 sx;
    s32 sy;
    s32 st;
    Ent *t;
    const char *msg;
    f32 v;
    s32 k;

    g = func_31A8D0();
    p506C = g->f506C;
    p5080 = g->f5080;
    p5178 = g->f5178;
    grid = g->f4960;
    insect_InsectSeqGetActors_51b7e0(&hit, 2, 3);
    a = hit.f00;
    b = hit.f04;
    n = hit.f08;
    if (a == 0 || n == 0 || b == 0) {
        return 1;
    }

    insect_InsectBoardFindPiece_4ee190(grid, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(grid, b, &bx, &by);
    lx = func_12DE98(bx - ax);
    ly = func_12DE98(by - ay);
    sx = bx;
    sx -= ax;
    sy = by;
    sy -= ay;
    if (lx != 0) {
        sx = sx / lx;
    }
    if (ly != 0) {
        sy = sy / ly;
    }

    switch (c->f4) {
    case 0:
        D_00485110 = 0;
        D_00485110 = insect_InsectBattleSpecialDamage_50fc50(a, b, n);
        if (D_00485110 <= 0 || insect_InsectPieceTestStatus_513280(a, 0x10) != 0) {
            msg = (const char *)g->f5F82;
            func_1343B8((void *)msg, insect_InsectMsgGet_512b70(p506C, 0x3A), n,
                        a->f5C);
            insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
            insect_InsectPlaySe_510870(7);
            insect_InsectBattleLogPush_51c2f0(p5080, msg, -5, -1, 0);
            return 1;
        }
        st = 2;
        D_00485108 = bx + sx;
        D_0048510C = by + sy;
        if (insect_InsectBoardInBounds_4efac0(grid, bx + sx, by + sy) != 0 &&
            insect_InsectBoardGetPiece_4ee9a0(grid, D_00485108, D_0048510C) == 0 &&
            insect_InsectPieceRollVsResist_512bf0(b, insect_InsectPieceGetStat_512e20(b, 0, 0),
                                a->f18) != 0) {
            st = 1;
        }
        if (st == 2) {
            D_00485108 = bx;
            D_0048510C = by;
        }
        c->f4 = st;
        break;
    case 1:
        insect_InsectBoardCellToWorld_4eda70(grid, &px, &py, &pz, 0, (f32)D_00485108,
                            (f32)D_0048510C);
        insect_InsectPieceMoveTo_5157d0(b, 0, px, py, pz, 10.0f);
        insect_InsectBattleEffectsSpawn_51dc30(p5178, b, 0x19, 0, 0, -1, -1, 1, 0);
        insect_InsectBattleApplyDamage_50f350(a, b, D_00485110, 0, 1);
        insect_InsectBattlePieceResetMotion_50f960(b);
        insect_InsectBoardTakeAt_4ef770(grid, bx, by);
        insect_InsectBoardPlacePiece_4ef830(grid, b, D_00485108, D_0048510C);
        c->f4 = 3;
        break;
    case 3:
        D_00485100 = 0;
        *(f32 *)&D_00481038 = D_0047DD48;
        *(f32 *)&D_00485104 = 0.0f;
        insect_InsectBoardFindPiece_4ee190(grid, b, &qx, &qy);
        if (insect_InsectBoardIsHole_4ee7e0(grid, qx, qy) != 0) {
            c->f4 = 4;
            return 0;
        }
        return 1;
    case 4:
        if (insect_InsectPieceIsMoveDone_514a20(b, ax, bx) != 0) {
            D_00485100 = D_00485100 + 1;
            if (D_00485100 == 10) {
                insect_InsectPlaySe_510870(2);
            }
            k = D_00485100;
            v = D_00485104;
            v += D_00481038;
            *(f32 *)&D_00481038 = D_00481038 + D_0047DD20;
            *(f32 *)&D_00485104 = v;
            b->fD8 = v;
            if (k >= 30) {
                c->f4 = 5;
            }
        }
        break;
    case 5:
        insect_InsectBoardFindPiece_4ee190(grid, b, &rx, &ry);
        insect_InsectPieceSetHp_512ee0(b, 0);
        insect_InsectBoardHoleClear_4ee780(grid, rx, ry);
        msg = (const char *)g->f5F82;
        func_1343B8((void *)msg, insect_InsectMsgGet_512b70(p506C, 0x9A),
                    b->f5C);
        insect_InsectBattleLogPush_51c2f0(p5080, msg, -5, -1, 0);
        return 1;
    case 2:
        st = 1;
        t = insect_InsectBoardGetPiece_4ee9a0(grid, D_00485108, D_0048510C);
        if (insect_InsectBoardInBounds_4efac0(grid, D_00485108, D_0048510C) != 0 && t != 0 &&
            insect_InsectPieceIsInPlay_5149e0(t) != 0 && insect_InsectPieceIsEnemyOf_5149b0(a, t) != 0) {
            insect_InsectBattleApplyDamage_50f350(a, t, D_00485110, 0, 1);
            insect_InsectBattleEffectsSpawn_51dc30(p5178, t, 0x19, 6, 0, -1, -1, 1, 0);
            st = 0;
            D_00485110 = D_00485110 >> 1;
        }
        if (st != 0) {
            return 1;
        }
        D_00485108 += (s8)sx;
        D_0048510C += (s8)sy;
        break;
    default:
        return 1;
    }
    return 0;
}
