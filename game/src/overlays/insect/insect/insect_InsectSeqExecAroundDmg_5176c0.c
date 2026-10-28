/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecAroundDmg_5176c0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x005176C0 -- 904 bytes, 226 instructions, 21 calls.
 * Two divide-by-zero traps (0x005178B8 and 0x005178F0), so this unit needs
 * `#pragma divbyzerocheck on` (levers.d/mwcc-divbyzerocheck-pragma).
 */

typedef struct H {
    u8   pad00[0x6A];
    s16  f6A;                       /* +0x6A */
} H;

typedef struct P {
    u8   pad00[0x0C];
    H   *f0C;                       /* +0x0C */
} P;

typedef struct Unit {
    u8   pad00[0x18];
    s8   f18;                       /* +0x18 */
    u8   pad19[0x1C - 0x19];
    s16  f1C;                       /* +0x1C */
    u8   pad1E[0x38 - 0x1E];
    s8   f38;                       /* +0x38 */
    u8   pad39[0x5C - 0x39];
    s32  f5C;                       /* +0x5C */
} Unit;

typedef struct A {
    u8   pad00[0x04];
    s32  f04;                       /* +0x04 */
    u8   pad08[0x0C - 0x08];
    s8   f0C;                       /* +0x0C */
    u8   pad0D;
    s16  f0E;                       /* +0x0E */
    s8   f10;                       /* +0x10 */
} A;

typedef struct G {
    u8   pad0000[0x4960];
    u8   f4960[0x506C - 0x4960];
    u8   f506C[0x5080 - 0x506C];
    u8   f5080[0x51C4 - 0x5080];
    u8   f51C4[0x5EF1 - 0x51C4];
    u8   f5EF1;
    u8   pad5EF2[0x5F82 - 0x5EF2];
    u8   f5F82;
} G;

/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *p, s32 v, H *h, s32 k);
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
extern f32  D_0047DD4C;

s32 insect_InsectSeqExecAroundDmg_5176c0(A *a)
{
    s32   ox;
    s32   oy;
    void *p120;
    void *p110;
    s32   lvl;
    s32   done;
    s32   ok;
    void *p5F82;
    s32   c;
    s32   d;
    G    *g;
    void *p30;
    void *p51C4;
    Unit *q;
    H    *h;
    P    *pp;
    s32   pw;
    s32   dmg;
    s32   cx;
    s32   cy;
    s32   y;
    s32   x;
    Unit *u;

    g = ((G *)InsectBattleGet_31a8d0());
    if (a == 0 || g == 0) {
        return 1;
    }

    p120 = g->f506C;
    p110 = g->f5080;
    p30 = g->f4960;
    q = ((Unit *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    p51C4 = g->f51C4;
    h = 0;
    if (q == 0) {
        return 1;
    }

    switch (g->f5EF1) {
    case 0:
        h = ((H *)insect_InsectBattleGetSpecialRec_50db30(g));
        break;
    case 1:
        pp = ((P *)insect_InsectAiGetAction_522300(p51C4));
        if (pp != 0) {
            h = pp->f0C;
        }
        break;
    }

    pw = 0;
    c = a->f0C;
    d = a->f10;
    lvl = a->f0E;
    if (h != 0) {
        lvl = h->f6A;
    }

    insect_InsectBoardFindPiece_4ee190(p30, q, &ox, &oy);

    switch (a->f04) {
    case 0:
        if (insect_InsectPieceGetMotionPhase_5142d0(q) < D_0047DD4C) {
            break;
        }
        a->f04 = a->f04 + 1;
        break;
    case 1:
        done = 0;
        for (y = -c; y <= c; y++) {
            for (x = -c; x <= c; x++) {
                cx = ox + x;
                cy = oy + y;
                if (insect_InsectBoardInBounds_4efac0(p30, (long long)(cx), (long long)(cy)) == 0) {
                    continue;
                }
                u = ((Unit *)insect_InsectBoardGetPiece_4ee9a0(p30, cx, cy));
                if (u != 0 && insect_InsectPieceIsInPlay_5149e0(u) != 0 &&
                    insect_InsectPieceIsEnemyOf_5149b0(u, q) != 0) {
                    if (d != 0) {
                        s32 s2 = u->f18;
                        s32 s1 = q->f18;
                        s32 rr = Rand_133710() % d;
                        pw = rr + (s1 + s2) * 5;
                    }
                    dmg = insect_InsectBattleCalcBaseDamage_50ffb0(q, u, pw);
                    dmg = dmg + Rand_133710() % pw;
                    ok = 1;
                    if (u->f38 == 12 && insect_InsectPieceTestStatus_513280(u, 0x18) == 0) {
                        ok = 0;
                        dmg = 0x270F;
                    }
                    if (ok != 0) {
                        insect_InsectPieceTryInflictByFlag_514b10(u, lvl, 1, 4);
                    }
                    p5F82 = &g->f5F82;
                    if (dmg > 0) {
                        insect_InsectBattleApplyDamage_50f350(q, u, dmg, 0, 0);
                        if (u->f1C > 0) {
                            insect_InsectBattlePieceFlipMotionMaybe_50f2a0(u);
                        }
                    } else {
                        Sprintf_1343b8(p5F82, ((s32)insect_InsectMsgGet_512b70(p120, 0x3A)), h,
                                    u->f5C);
                        insect_InsectBattleLogPush_51c2f0(p110, p5F82, -5, -1, 0);
                        if (done == 0) {
                            insect_InsectPlaySe_510870(7);
                            done = 1;
                        }
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}
