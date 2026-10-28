/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowCpuTurn_5093e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005093E0 -- 1,812 bytes, 453 instructions, 65 calls, 42 conditional
 * branches, br/ins 0.093.  A thirteen-arm state dispatch of the
 * insect_InsectBattleGetStep_50d6a0(o, 0) family, from x_large.py's large end.
 *
 * The compare CHAIN runs 0xB, 0x38, 0x37, 8, 0x36, 0x35, 0x34, 0x33, 0x32,
 * 0x31, 0x1C, 0x1B, 1 -- REVERSED -- so source case order is 1, 0x1B, 0x1C,
 * 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 8, 0x37, 0x38, 0xB, and the thirteen
 * blocks are laid out in exactly that order.  There is no empty case and no
 * orphaned block: unlike insect_InsectBattleFlowTeamSelectInput_507c80 every arm here is a plain
 * `break;`.
 *
 * Case 0x1B FALLS THROUGH into case 0x1C.  Its `insect_InsectBattleGetState_50d6f0(o, 5)`
 * guard is spelled as an early `break;` on the != 0 side, so the fall-through
 * is the body.
 *
 * o->f51C4, o->f4960, o->f4F90 and o->f35F8 are all REMATERIALISED at every
 * site (bare `addiu $4, $16, K`), so all four stay array members written
 * inline.
 *
 * Cases 0x35 and 0x37 are the same block twice, and the `dsll32 24 / dsra32
 * 24` between their two stores is mwcc forwarding the s8 it just stored and
 * re-narrowing it -- two plain `n->f14 &= ~K;` statements, not one expression.
 *
 * Case 0x36's four record stores come out 0x5B28, 0x5B20, 0x5B2C, 0x5B24 --
 * two DESCENDING pairs, so two chained assignments -- while case 0x34's come
 * out 0x5B20, 0x5B24, 0x5B28, 0x5B2C and are four separate statements.
 * insect-chained-assignment, both polarities in one function.
 *
 * Case 0x31's `fl &= ~4` guard is the inverted-|| chain: the `bnel` / `bnez` /
 * `bgtzl` sequence with the -5 materialised twice says
 * `if (A != 0 || B != 0 || e->f4F <= 0)`, and the three-way test after it is a
 * plain if / else if / else if with the FALL-THROUGH arm (`fl & 1`) first.
 */

typedef struct Rec {
    void *f00;                      /* +0x00 */
    void *f04;                      /* +0x04 */
    u8    pad08[0x0C - 0x08];
    void *f0C;                      /* +0x0C */
    s8    f10;                      /* +0x10 */
    s8    f11;                      /* +0x11 */
    s8    f12;                      /* +0x12 */
    s8    f13;                      /* +0x13 */
    s8    f14;                      /* +0x14 */
} Rec;

typedef struct Ent {
    u8 pad00[0x4F];
    s8 f4F;                         /* +0x4F */
    u8 pad50[0x62 - 0x50];
    s8 f62;                         /* +0x62 */
} Ent;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                     /* +0x0878 */
    u8    pad87C[0x35F8 - 0x87C];
    u8    f35F8[0x4960 - 0x35F8];   /* +0x35F8, records at a 0x994 stride */
    u8    f4960[0x4F90 - 0x4960];   /* +0x4960 */
    u8    f4F90[0x51C4 - 0x4F90];   /* +0x4F90 */
    u8    f51C4[0x5AF4 - 0x51C4];   /* +0x51C4 */
    u8    f5AF4;                    /* +0x5AF4 */
    u8    pad5AF5[0x5B18 - 0x5AF5];
    void *f5B18;                    /* +0x5B18 */
    void *f5B1C;                    /* +0x5B1C */
    void *f5B20;                    /* +0x5B20 */
    void *f5B24;                    /* +0x5B24 */
    void *f5B28;                    /* +0x5B28 */
    void *f5B2C;                    /* +0x5B2C */
    u8    pad5B30[0x5DA8 - 0x5B30];
    s32   f5DA8;                    /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                    /* +0x5EF1 */
} Ins;

extern s32 insect_D_00523D30[8];

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

void insect_InsectBattleFlowCpuTurn_5093e0(Ins *o)
{
    s32   x7C;
    s32   x78;
    s32   x74;
    s32   x70;
    s32   x6C;
    s32   x68;
    s32   code;
    s32   fl;
    void *ent;
    Rec  *n;
    s32   ok;
    s32   i;
    s32   a;
    s32   b;
    s32   c;
    const s32 *t;
    s32   j;
    void *p;
    void *q;
    void *h;
    Ent  *w;
    s32   v;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        UiSetWidgetVisible_290010(o->f878, 0x7592, 1, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        break;
    case 0x1B:
        if (insect_InsectBattleGetState_50d6f0(o, 5) != 0) {
            break;
        }
        insect_InsectAiBeginTurn_522ba0(o->f51C4);
        o->f5AF4 = o->f5EF1;
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        /* fall through */
    case 0x1C:
        insect_InsectAiThink_522a90(o->f51C4, o->f5DA8);
        if (insect_InsectAiGetState_522a50(o->f51C4) == 8) {
            v = 0xB;
            if (((Rec *)insect_InsectAiGetAction_522300(o->f51C4)) != 0) {
                v = 0x31;
            }
            insect_InsectBattleSetStep_50d7a0(o, v, 0, -1);
        }
        break;
    case 0x31:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if (n != 0) {
            ent = n->f00;
            fl = n->f14;
            code = 0x38;
            if ((insect_InsectPieceTestStatus_513280(ent, 0x18) != 0) ||
                (insect_InsectPieceTestStatus_513280(ent, 0x19) != 0) ||
                (((Ent *)ent)->f4F <= 0)) {
                fl &= ~4;
            }
            if (fl & 1) {
                code = 0x32;
            } else if (fl & 4) {
                code = 0x36;
            } else if (fl & 2) {
                insect_InsectBoardFindPiece_4ee190(o->f4960, ent, &x7C, &x78);
                insect_InsectBoardFindPiece_4ee190(o->f4960, n->f04, &x74, &x70);
                insect_InsectBoardMarkAdjacentTargets_4ecf80(o->f4960, ent, x7C, x78);
                if (insect_InsectBoardIsTargetMarked_4ee8c0(o->f4960, x74, x70) != 0) {
                    code = 0x34;
                }
            }
            insect_InsectBattleSetStep_50d7a0(o, code, 0, -1);
        }
        break;
    case 0x32:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if (n != 0) {
            p = n->f00;
            o->f5B1C = p;
            a = n->f10;
            b = n->f11;
            insect_InsectBoardFindPiece_4ee190(o->f4960, p, &x6C, &x68);
            insect_InsectBoardMovePiece_4ed8f0(o->f4960, x6C, x68, a, b);
            insect_InsectCursorSetPageSetCell_511c20(o->f4F90, ((s32)insect_InsectCursorSetFindPage_511e60(o->f4F90, 3)), a, b);
            insect_InsectBattleSetState_50d8c0(o, 1, 3, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x33, 0, -1);
        }
        break;
    case 0x33:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if ((n != 0) && (insect_InsectBattleGetStep_50d6a0(o, 3) == 0xB)) {
            n->f14 &= ~1;
            insect_InsectBattleSetStep_50d7a0(o, 0x31, 0, -1);
        }
        break;
    case 0x34:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if (n != 0) {
            p = n->f00;
            q = n->f04;
            o->f5B20 = p;
            o->f5B24 = q;
            o->f5B28 = p;
            o->f5B2C = q;
            insect_InsectBattleSetState_50d8c0(o, 2, 3, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x35, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x32);
            insect_InsectBattleSetFlag_50dad0(o, 0x33);
        }
        break;
    case 0x35:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if ((n != 0) && (insect_InsectBattleGetStep_50d6a0(o, 3) == 0xB)) {
            n->f14 &= ~2;
            n->f14 &= ~4;
            insect_InsectBattleSetStep_50d7a0(o, 0x31, 0, -1);
            insect_InsectBattleClearFlag_50da90(o, 0x32);
            insect_InsectBattleClearFlag_50da90(o, 0x33);
        }
        break;
    case 0x36:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if (n != 0) {
            h = insect_InsectBoardGetPiece_4ee9a0(o->f4960, n->f12, n->f13);
            p = n->f00;
            o->f5B20 = o->f5B28 = p;
            o->f5B24 = o->f5B2C = h;
            w = n->f0C;
            o->f5B18 = w;
            insect_InsectBattleSetStep_50d7a0(o, 8, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 9, 1, -1);
            if (w != 0) {
                c = w->f62;
                t = insect_D_00523D30;
                insect_InsectBattleSetFlag_50dad0(o, 0x32);
                insect_InsectBattleSetFlag_50dad0(o, 0x33);
                for (j = 0; j < 8; j++, t++) {
                    if (c == *t) {
                        insect_InsectBattleClearFlag_50da90(o, 0x32);
                        insect_InsectBattleClearFlag_50da90(o, 0x33);
                        break;
                    }
                }
            }
        }
        break;
    case 8:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, 3, 3, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x37, 0, -1);
        }
        break;
    case 0x37:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if ((n != 0) && (insect_InsectBattleGetStep_50d6a0(o, 3) == 0xB)) {
            n->f14 &= ~2;
            n->f14 &= ~4;
            insect_InsectBattleSetStep_50d7a0(o, 0x31, 0, -1);
            insect_InsectBattleClearFlag_50da90(o, 0x32);
            insect_InsectBattleClearFlag_50da90(o, 0x33);
        }
        break;
    case 0x38:
        n = ((Rec *)insect_InsectAiGetAction_522300(o->f51C4));
        if (n != 0) {
            ent = n->f00;
            if (ent != 0) {
                insect_InsectPieceSetActed_514c90(ent);
            }
        }
        ok = 1;
        for (i = 0; i < 2; i++) {
            if (insect_InsectTeamAllActed_513690((u8 *)o + i * 0x994 + 0x35F8, o->f5EF1) == 0) {
                ok = 0;
            }
        }
        if (ok != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
            insect_InsectBattleClearFlag_50da90(o, 0xB);
        } else {
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        }
        break;
    case 0xB:
        insect_InsectTeamMarkAllActed_513540(o->f35F8, o->f5EF1);
        insect_InsectTeamMarkAllActed_513540((u8 *)o + 0x3F8C, o->f5EF1);
        insect_InsectBattleSetState_50d8c0(o, 1, 5, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    }
}
