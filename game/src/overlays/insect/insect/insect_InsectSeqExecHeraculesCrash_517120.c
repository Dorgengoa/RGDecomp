/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecHeraculesCrash_517120 1
#include "port/game_protos.h"
#line 1
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
 * flinch timer and 5 finishes.  The jump table insect_jtbl_005252F0 is dense 0..5 but
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
extern f32 D_00485104 __attribute__((section(".sbss")));              /* _gp - 0x6C */
extern f32 D_00481038 __attribute__((section(".sbss")));              /* _gp - 0x4138 */
extern f32 D_0047DD48;              /* _gp - 0x7428 */
extern f32 D_0047DD20;              /* _gp - 0x7450 */

/*rgp*/
extern void Sprintf_1343b8(void *dst, const char *fmt, ...);
extern s32  abs(s32 v);

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
    Hit hit __attribute__((aligned(16)));
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

    g = ((Ctx *)InsectBattleGet_31a8d0());
    p506C = g->f506C;
    p5080 = g->f5080;
    p5178 = g->f5178;
    grid = g->f4960;
    insect_InsectSeqGetActors_51b7e0(&hit);
    a = hit.f00;
    b = hit.f04;
    n = hit.f08;
    if (a == 0 || n == 0 || b == 0) {
        return 1;
    }

    insect_InsectBoardFindPiece_4ee190(grid, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(grid, b, &bx, &by);
    lx = abs(bx - ax);
    ly = abs(by - ay);
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
            Sprintf_1343b8((void *)msg, ((const char *)insect_InsectMsgGet_512b70(p506C, 0x3A)), n,
                        a->f5C);
            insect_InsectBattleDamagePopupSpawn_50f730(b, -1, 0x80402080);
            insect_InsectPlaySe_510870(7);
            insect_InsectBattleLogPush_51c2f0(p5080, msg, -5, -1, 0);
            return 1;
        }
        st = 2;
        D_00485108 = bx + sx;
        D_0048510C = by + sy;
        if (insect_InsectBoardInBounds_4efac0(grid, (long long)(bx + sx), (long long)(by + sy)) != 0 &&
            ((Ent *)insect_InsectBoardGetPiece_4ee9a0(grid, D_00485108, D_0048510C)) == 0 &&
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
        insect_InsectBattleEffectsSpawn_51dc30(p5178, b, 0x19, 0, 0, -1, -1, 1, (int)(0));
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
        if (insect_InsectPieceIsMoveDone_514a20(b) != 0) {
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
        Sprintf_1343b8((void *)msg, ((const char *)insect_InsectMsgGet_512b70(p506C, 0x9A)),
                    b->f5C);
        insect_InsectBattleLogPush_51c2f0(p5080, msg, -5, -1, 0);
        return 1;
    case 2:
        st = 1;
        t = ((Ent *)insect_InsectBoardGetPiece_4ee9a0(grid, D_00485108, D_0048510C));
        if (insect_InsectBoardInBounds_4efac0(grid, (long long)(D_00485108), (long long)(D_0048510C)) != 0 && t != 0 &&
            insect_InsectPieceIsInPlay_5149e0(t) != 0 && insect_InsectPieceIsEnemyOf_5149b0(a, t) != 0) {
            insect_InsectBattleApplyDamage_50f350(a, t, D_00485110, 0, 1);
            insect_InsectBattleEffectsSpawn_51dc30(p5178, t, 0x19, 6, 0, -1, -1, 1, (int)(0));
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
