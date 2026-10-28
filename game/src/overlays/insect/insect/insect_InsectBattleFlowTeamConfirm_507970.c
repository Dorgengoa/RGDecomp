/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTeamConfirm_507970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00507970 -- 784 bytes, 196 instructions.
 *
 * The 0x506C sibling of insect_InsectBattleFlowTurnEnd_509150: one state dispatch, every arm a
 * `beql` INTO its block, so the source case order is the compare chain
 * REVERSED (insect-dispatch-branch-polarity): 1, 0xA, 0x1D, 0x1E, 0xB.
 *
 * The two indexed sub-objects are written the way insect_InsectBattleFlowPlaceTeam_502c20 spells
 * them, `(u8 *)o + k * SIZE + BASE`, while `&o->f4F90` has to stay a struct
 * member address or mwcc CSEs the four `addiu $4, $18, 0x4F90` into one.
 */

typedef struct Obj {
    u8  pad0000[0x4F90];
    u8  f4F90[0x4FBC - 0x4F90];     /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x506C - 0x4FBD];
    u8  f506C[0x5DA8 - 0x506C];     /* +0x506C */
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5EF1 - 0x5DAC];
    u8  f5EF1;                      /* +0x5EF1 */
    u8  pad5EF2[0x5FC8 - 0x5EF2];
    f32 f5FC8;                      /* +0x5FC8 */
} Obj;

extern u8 insect_D_00523D50[];

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

void insect_InsectBattleFlowTeamConfirm_507970(Obj *o)
{
    s32   sp5C;
    s32   sp58;
    void *p;
    s32   n;
    s32   a;
    s32   b;
    void *u;
    void *t;
    s32   m;
    s32   k;

    p = o->f506C;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 8, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0xA:
        if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0x1A) {
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &sp5C, &sp58);
            n = -1;
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                n = sp5C;
            }
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                if (n == -1) {
                    n = 1;
                }
            }
            if (n != -1) {
                a = 0x1D;
                b = 6;
                if (n == 0) {
                    a = 0x1E;
                    b = 5;
                }
                insect_InsectBattleSetStep_50d7a0(o, a, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, a, 0, -1);
                insect_InsectBattlePlaySe_4f45b0(o, b);
            }
        }
        break;
    case 0x1D:
        if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, 7, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 7, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1A, 2, -1);
            insect_InsectCursorSetPopPage_511ca0(o->f4F90);
            u = (u8 *)o + o->f5EF1 * 0x20 + 0x4920;
            if (u != 0) {
                insect_InsectTeamSlotRemoveMember_514100(u, insect_InsectTeamSlotGetMember_513eb0(u, 4));
                insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523D50, 1);
                o->f4FBC = o->f4FBC & 0xFD;
            }
        }
        break;
    case 0x1E:
        k = o->f5EF1;
        t = (u8 *)o + k * 0x994 + 0x35F8;
        u = (u8 *)o + k * 0x20 + 0x4920;
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            m = 0xC;
            if (o->f5EF1 == 1) {
                m = 0xD;
            }
            insect_InsectTeamSlotSetName_5140f0(u, ((s32)insect_InsectMsgGet_512b70(p, m)));
        } else {
            insect_InsectTeamSlotSetName_5140f0(u, ((s32)insect_InsectMsgGet_512b70(p, 0xB)));
        }
        insect_InsectTeamReset_513d00(t, o->f5FC8);
        insect_InsectTeamSetSide_513cf0(t, o->f5EF1);
        insect_InsectTeamBuild_513920(t, u, o->f5EF1, o->f5DA8);
        insect_InsectBattleSetState_50d8c0(o, 9, 0, -1);
        insect_InsectBattleSetFlag_50dad0(o, 9);
        insect_InsectBattleSetFlag_50dad0(o, 0xA);
        o->f4FBC = o->f4FBC | 2;
        break;
    case 0xB:
        break;
    }
}
