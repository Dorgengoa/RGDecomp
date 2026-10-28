/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuActionCmd_4fd470 1
#include "port/game_protos.h"
#line 1
/* MATCHING (ix48, session 48).  Byte-identical to retail. */
#include "types.h"
/* insect 0x004FD470 -- 1,300 bytes, 325 instructions, 52 calls, 16 conditional
 * branches, br/ins 0.049.  An eight-arm state dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 2), the insect_InsectBattleMenuTeamSelect_5004f0 family; read that unit's
 * prototype block first.
 *
 * The compare chain runs 0xB, 0x20, 0x1C, 0x21, 0x2C, 0x1D, 0x15, 1 --
 * REVERSED -- so the source case order is 1, 0x15, 0x1D, 0x2C, 0x21, 0x1C,
 * 0x20, 0xB, which is the block order (0xD520, 0xD698, 0xD6F4, 0xD7CC,
 * 0xD81C, 0xD860, 0xD878, 0xD930) forwards.  Case 1 FALLS THROUGH into 0x15.
 *
 * insect_InsectBoardGetPiece_4ee9a0's coordinates are s16 (see insect_InsectBattleFlowSpecialSelect_5040a0, where
 * the same callee takes s8 + s8 SUMS and grows a `dsll32 16 / dsra32 16`
 * pair).  Here the arguments are bare s8 fields, so `lb` alone is the whole
 * conversion and nothing extra appears.
 *
 * The case-1 loop RE-EVALUATES its bound: `insect_InsectCmdMenuCount_4efc10` is called at
 * the top of every iteration, so the count belongs in the `for` condition and
 * not in a hoisted local.
 *
 * PARKED -- RIGHT LENGTH (0x514, 325 of 325 words) AND **2** DIFFERING WORDS,
 * so it is deliberately NOT in config/ocunits/insect.txt.  The link's length
 * guard cannot catch this shape.
 *
 * The entire residue is a two-instruction TRANSPOSITION in the entry block:
 * retail schedules `lb $6, 0x9($2)` / `addiu $17, $18, 0x4960` /
 * `lb $5, 0x8($2)`, we schedule the two `lb`s the other way round with the
 * same `addiu` between them.  Everything else -- all eight dispatch arms, the
 * fall-through, every branch kind, the frame -- is byte-identical.
 *
 * CLOSED, ix48: the residue was `f(e, s->m8, s->m9)` -- retail evaluates the
 * two byte arguments RIGHT TO LEFT (`lb $a2,9` before `lb $a1,8`) and we
 * evaluated them in argument order.  The lever is the VOLATILE ACCESS-SITE PIN
 * on the `m9` read, taken before `e`:
 *     y = *(volatile s8 *)&s->m9;
 * A plain temporary does not work because mwcc PROPAGATES the name away and
 * re-materialises the read at the call; `volatile` pins it at the access site,
 * and the pin costs no instruction (the `lb` is the whole access either way).
 * Session 24 measured 130 arms and read a "scheduler tie-break, stop" floor:
 * `s8`/`s16`/`s32`/`u8` parameter types in every combination, a K&R prototype,
 * a temporary for the second argument, a temporary for BOTH arguments in
 * reverse order, `((s8 *)s)[8]`, an explicit `(s16)` cast, `(u8 *)o + 0x4960`
 * inline, and all 120 permutations of the five pointer/`Slot` declarations --
 * every one of them 2 bad.  Session 48 added four pragmas on AND off
 * (`opt_defineargorder`, `opt_serializeassignments`, `opt_prelinearize`,
 * `opt_movepostops`) and eight more structural forms in a standalone probe TU
 * (`build/ix48/argprobe.c`): also one object.  The pin was the only thing that
 * moved it, and it moved it straight to MATCH.
 *
 * Everything else here IS solved and transfers:
 *   - the 0x26 guard is spelled `== 0` with the one-call arm FIRST; written
 *     `!= 0` with the arms swapped it costs five reordered gaps;
 *   - the case-1 loop RE-EVALUATES insect_InsectCmdMenuCount_4efc10 every iteration, so the
 *     bound belongs in the `for` condition and not in a hoisted local.
 */

typedef struct Slot {
    u8 pad00[0x8];
    s8 m8;                      /* +0x08 */
    s8 m9;                      /* +0x09 */
    s8 mA;                      /* +0x0A */
    s8 mB;                      /* +0x0B */
} Slot;

typedef struct Rec {
    u8  pad00[0x5C];
    s32 m5C;                    /* +0x5C */
} Rec;

typedef struct Ins {
    u8   pad0000[0x878];
    void *m878;                 /* +0x0878 */
    void *m87C;                 /* +0x087C */
    u8   pad0880[0x4960 - 0x880];
    u8   m4960[0x4F90 - 0x4960];/* +0x4960 */
    u8   m4F90[0x2C];           /* +0x4F90 */
    u8   m4FBC;                 /* +0x4FBC */
    u8   pad4FBD[0x502C - 0x4FBD];
    u8   m502C[0x5B1C - 0x502C];/* +0x502C */
    Rec *m5B1C;                 /* +0x5B1C */
} Ins;

extern u8 insect_D_00523F90[];

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

void insect_InsectBattleMenuActionCmd_4fd470(Ins *o)
{
    void *e;
    Rec *t;
    Slot *s;
    Slot *u;
    Slot *v;
    s32 n;
    s32 i;
    s16 y;

    s = ((Slot *)insect_InsectCursorSetFindPage_511e60(o->m4F90, 0xA));
    y = *(volatile s8 *)&s->m9;
    e = o->m4960;
    t = ((Rec *)insect_InsectBoardGetPiece_4ee9a0(e, s->m8, y));

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectCmdMenuClear_4efd40(o->m502C);
        if (insect_InsectPieceTestStatus_513280(t, 0x26) == 0) {
            insect_InsectCmdMenuAdd_4efc80(o->m502C, 1);
        } else {
            if (insect_InsectBoardHasAdjacentEnemy_4ef670(e, t) != 0) {
                insect_InsectCmdMenuAdd_4efc80(o->m502C, 0);
            }
            if (insect_InsectPieceTestStatus_513280(t, 0x28) == 0) {
                insect_InsectCmdMenuAdd_4efc80(o->m502C, 2);
            }
            insect_InsectCmdMenuAdd_4efc80(o->m502C, 4);
        }
        insect_InsectCmdMenuAdd_4efc80(o->m502C, 6);
        insect_InsectCmdMenuAdd_4efc80(o->m502C, 3);
        insect_InsectCmdMenuAdd_4efc80(o->m502C, 5);
        n = insect_InsectCmdMenuCount_4efc10(o->m502C);
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 4, 1);
        u = ((Slot *)insect_InsectCursorSetFindPage_511e60(o->m4F90, 4));
        if (u != 0) {
            u->m9 = 0;
            u->m8 = 0;
            u->mB = 0;
            u->mA = 0;
        }
        insect_InsectCursorSetSetSize_511bd0(o->m4F90, 1, n);
        o->m4FBC = o->m4FBC & 0xFD;
        insect_InsectCmdMenuLayout_4fab80(o, 3, 1, t->m5C);
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        UiSetTextString_28f510(o->m878, 0x7564, t->m5C, 0);
        for (i = 0; i < insect_InsectCmdMenuCount_4efc10(o->m502C); i += 1) {
            insect_InsectCmdMenuEntryRefresh_4f0060(o, i, t);
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x15, 2, -1);
        /* fall through */
    case 0x15:
        UiSetWidgetVisible_290010(o->m878, 0x7564, 1, -1);
        UiSetWidgetVisible_290010(o->m878, 0x7589, insect_InsectPieceIsKing_514b00(t), -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523F90, 1);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->m878, 0x755F, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        o->m5B1C = t;
        insect_InsectBoardRestore_4ed9d0(e);
        s = ((Slot *)insect_InsectCursorSetFindPage_511e60(o->m4F90, 2));
        v = ((Slot *)insect_InsectCursorSetFindPage_511e60(o->m4F90, 0xA));
        v->m8 = s->m8;
        v->m9 = s->m9;
        v->mA = s->mA;
        v->mB = s->mB;
        u = ((Slot *)insect_InsectCursorSetFindPage_511e60(o->m4F90, 4));
        if (u != 0) {
            u->m9 = 0;
            u->m8 = 0;
            u->mB = 0;
            u->mA = 0;
        }
        insect_InsectBattleSetState_50d8c0(o, 1, 3, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x2C, 2, -1);
        break;
    case 0x2C:
        if (insect_InsectBattleGetStep_50d6a0(o, 3) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 0), 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        }
        break;
    case 0x21:
        UiFadeWidgetAlpha_290690(o->m878, 0x755F, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        break;
    case 0x1C:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523F90, 0);
        break;
    case 0x20:
        UiFadeWidgetAlpha_290690(o->m878, 0x7565, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m878, 0x755F, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m878, 0x7530, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        if (UiGetWidgetAlpha_290770(o->m878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0xB:
        UiFadeWidgetAlpha_290690(o->m878, 0x755F, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->m87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        break;
    }
}
