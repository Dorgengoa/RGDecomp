/* rgp:protos */
#define RGP_SELF_normal_FieldHudStep_4f56d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F56D0 -- the party-formation panel's per-frame TICK: a
 * registration LIST.  After two guards it calls sixteen single-argument
 * updaters on the panel in a fixed order, with one entity sweep in the middle
 * that re-reads the world handle from the root every iteration.
 *
 * Found by the main-side pass-33 LIST rank (levers.d/main-pass33-lists): 288
 * bytes, 72 instructions, FOUR conditional branches and 22 calls.  Size says
 * "medium unit"; the branch count says "transcription".
 *
 * Both guards are EARLY RETURNS on the negated condition, so the panel body is
 * what FALLS THROUGH -- the recorded guard-polarity rule.  They land on two
 * different labels only because the first one's `ld $31` rides its own
 * branch-likely slot and the second one's does not.
 *
 * `normal_FieldHudPanelsFadeUpdate_4f6d30` is declared `(void)` in normal_FieldHudPartyPanelsStep_4f57f0.cpp and
 * takes the panel HERE: its argument setup is the `daddu $4,$19,$0` in the
 * jal's own delay slot.  Arity is read off the argument SETUP, not off a
 * neighbouring TU's prototype.
 *
 * The `lw $4,0x18($17)` in the loop-test's branch-likely slot is `q->f018`
 * RE-READ each iteration, which is what a direct `func_3C2420(q->f018, i)`
 * emits -- the identical loop is already byte-identical in 004F57F0. */

typedef struct Root {
    u8    pad000[0x18];
    void *f018;
} Root;

typedef struct Obj {
    u8  pad000[0x14];
    u8  f014[0x28 - 0x14];
    u8  f028[0x378 - 0x28];
    s16 f378;
} Obj;

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

extern void normal_FieldHudStep_4f56d0(Obj *p);

void normal_FieldHudStep_4f56d0(Obj *p)
{
    Root *q;
    void *o;
    s32   n;
    s32   i;

    q = ((Root *)GetGameData_1fede0());
    if (q == 0) {
        return;
    }
    if (p->f378 == 0) {
        return;
    }
    normal_FieldHudTacticsModeIconRefresh_4f7be0(p);
    normal_FieldHudPanelsFadeUpdate_4f6d30(p);
    normal_FieldHudPartyPanelsStep_4f57f0(p);
    normal_FieldHudPanelActionChipsUpdateMaybe_4f5f00(p);
    normal_FieldHudPanelFlashUpdate_4f50f0(p);
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        o = PartyGetMemberChara_3c2420(q->f018, i);
        if (o != 0) {
            CharaIsPartyLeader_3ae1a0(o);
        }
    }
    normal_FieldHudRadarUpdate_4f4050(p);
    normal_FieldHudEnemyListUpdateMaybe_4f13d0(p);
    normal_FieldHudRadarSlideOutCheck_4f1740(p);
    normal_FieldHudHintTimersUpdateMaybe_4f8f10(p);
    normal_FieldHudMissionBannerUpdateMaybe_4f1eb0(p);
    normal_FieldHudPartyPanelShakeStep_4f4880(p);
    normal_FieldHudPanelHealGlowUpdate_4f2d50(p);
    normal_FieldHudLogUpdate_4f8930(p);
    normal_FieldHudAllySuggestStep_4ef070(p);
    normal_FieldHudAttackChainUpdate_4f61b0(p);
    UiUpdateWidgets_2913a0(p);
    UiUpdateWidgets_2913a0(p->f014);
    BattleSparkBurstUpdate_3831d0(p->f028);
}
