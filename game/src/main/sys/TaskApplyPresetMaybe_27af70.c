/* rgp:protos */
#define RGP_SELF_TaskApplyPresetMaybe_27af70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The debug task registry: one switch on the game mode, twelve cases,
   each a straight list of named step/draw task registrations.  Case
   ORDER is read off the jump table at 0x0045FE80 -- the physical block
   order is the SOURCE order (1, 0, 7, 3, 2, 4, 5, 11, 8, 9, 6, 10),
   and the table is the permutation.  The names are retail's own
   strings ("Chara Think", "Draw Sand Storm", ...), so they are the one
   recovered thing in this file. */

struct Prof;
struct Prof { u8 pad000[0x8]; s32 m08; };

extern char D_0045F920[];
extern char D_0045F930[];
extern char D_0045F940[];
extern char D_0045F950[];
extern char D_0045F998[];
extern char D_0045F9A8[];
extern char D_0045F9B8[];
extern char D_0045F9D0[];
extern char D_0045F9F0[];
extern char D_0045FA08[];
extern char D_0045FA18[];
extern char D_0045FA28[];
extern char D_0045FA38[];
extern char D_0045FA48[];
extern char D_0045FA60[];
extern char D_0045FA78[];
extern char D_0045FA88[];
extern char D_0045FA98[];
extern char D_0045FAA8[];
extern char D_0045FAB8[];
extern char D_0045FAC8[];
extern char D_0045FAD8[];
extern char D_0045FAF0[];
extern char D_0045FB10[];
extern char D_0045FB30[];
extern char D_0045FB48[];
extern char D_0045FB60[];
extern char D_0045FB80[];
extern char D_0045FB90[];
extern char D_0045FBA0[];
extern char D_0045FBB0[];
extern char D_0045FBC0[];
extern char D_0045FBE0[];
extern char D_0045FC00[];
extern char D_0045FC20[];
extern char D_0045FC40[];
extern char D_0045FC60[];
extern char D_0045FC70[];
extern char D_0045FC88[];
extern char D_0045FC98[];
extern char D_0045FCA8[];
extern char D_0045FCB8[];
extern char D_0045FCC8[];
extern char D_0045FCD8[];
extern char D_0045FCE8[];
extern char D_0045FCF0[];
extern char D_0045FD00[];
extern char D_0045FD10[];
extern char D_0045FD20[];
extern char D_0045FD30[];
extern char D_0045FD40[];
extern char D_0045FD50[];
extern char D_0045FD70[];
extern char D_0045FD80[];
extern char D_0045FDA0[];
extern char D_0045FDB0[];
extern char D_0045FDC0[];
extern char D_0045FDD0[];
extern char D_0045FDE0[];
extern char D_0045FDF0[];
extern char D_0045FE10[];
extern char D_0045FE28[];
extern char D_0045FE38[];
extern char D_0045FE48[];
extern char D_0045FE58[];
extern char D_0045FE70[];

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
void TaskApplyPresetMaybe_27af70(s32 mode) {
    s32 h;

    switch (mode) {
    case 1:
        TaskEnableEventFieldSetMaybe_287250();
        return;
    case 0:
        TaskTableRestoreOrder_27bed0();
        TaskEnableEventSceneSetMaybe_286f40();
        GetDrawCtx_15de80();
        return;
    case 7:
        TaskEnableEventSceneSetMaybe_286f40();
        TaskMoveBefore_27bf50(D_0045F998, D_0045F9A8);
        TaskMoveBefore_27bf50(D_0045F9B8, D_0045F9A8);
        return;
    case 3:
        TaskEnableBattleSet_2873f0();
        TaskSetUpdateTasksPaused_287dd0(1);
        TaskSetEnabled_27c2a0(1, D_0045F9D0);
        TaskSetEnabled_27c2a0(1, D_0045F9F0);
        TaskSetEnabled_27c2a0(1, D_0045FA08);
        TaskSetEnabled_27c2a0(0, D_0045F950);
        return;
    case 2:
        TaskEnableBattleSet_2873f0();
        TaskSetEnabled_27c2a0(1, D_0045F9B8);
        TaskSetEnabled_27c2a0(1, D_0045FA18);
        TaskSetEnabled_27c2a0(1, D_0045FA28);
        TaskSetEnabled_27c2a0(1, D_0045FA38);
        TaskSetEnabled_27c2a0(1, D_0045FA48);
        TaskSetEnabled_27c2a0(1, D_0045FA60);
        TaskSetEnabled_27c2a0(1, D_0045FA78);
        TaskSetEnabled_27c2a0(1, D_0045FA88);
        TaskSetEnabled_27c2a0(0, D_0045FA98);
        TaskSetEnabled_27c2a0(0, D_0045FAA8);
        TaskSetEnabled_27c2a0(0, D_0045FAB8);
        TaskSetEnabled_27c2a0(0, D_0045F920);
        TaskSetEnabled_27c2a0(0, D_0045F940);
        TaskSetEnabled_27c2a0(0, D_0045F930);
        TaskSetEnabled_27c2a0(0, D_0045FAC8);
        TaskSetEnabled_27c2a0(0, D_0045FAD8);
        TaskSetEnabled_27c2a0(0, D_0045FAF0);
        TaskSetEnabled_27c2a0(0, D_0045FB10);
        TaskSetEnabled_27c2a0(0, D_0045FB30);
        TaskSetEnabled_27c2a0(0, D_0045F9D0);
        TaskSetEnabled_27c2a0(0, D_0045F9F0);
        TaskSetEnabled_27c2a0(0, D_0045FB48);
        TaskSetEnabled_27c2a0(0, D_0045FB60);
        TaskSetEnabled_27c2a0(0, D_0045FB80);
        TaskSetEnabled_27c2a0(0, D_0045FB90);
        TaskSetEnabled_27c2a0(0, D_0045FBA0);
        TaskSetEnabled_27c2a0(0, D_0045FBB0);
        TaskSetEnabled_27c2a0(0, D_0045FBC0);
        TaskSetEnabled_27c2a0(0, D_0045FBE0);
        TaskSetEnabled_27c2a0(0, D_0045FC00);
        TaskSetEnabled_27c2a0(0, D_0045FC20);
        TaskSetEnabled_27c2a0(0, D_0045FC40);
        TaskSetEnabled_27c2a0(0, D_0045FC60);
        TaskSetEnabled_27c2a0(0, D_0045F950);
        TaskMoveBefore_27bf50(D_0045F998, D_0045F9A8);
        TaskMoveBefore_27bf50(D_0045F9B8, D_0045F9A8);
        EffectReleaseCharaEffectsAllMaybe_27a210();
        GameSceneCBlurReset_2f1e20();
        SceneScreenOverlayResetMaybe_2f1ea0();
        return;
    case 4:
        TaskEnableEventSceneSetMaybe_286f40();
        TaskSetRenderTasksEnabled_287b90(0);
        TaskSetEnabled_27c2a0(1, D_0045F9B8);
        TaskSetEnabled_27c2a0(1, D_0045FA18);
        TaskSetEnabled_27c2a0(1, D_0045FC70);
        TaskSetEnabled_27c2a0(1, D_0045FC88);
        TaskSetEnabled_27c2a0(1, D_0045FC98);
        TaskSetEnabled_27c2a0(0, D_0045FAA8);
        TaskSetEnabled_27c2a0(0, D_0045F940);
        TaskSetEnabled_27c2a0(0, D_0045FCA8);
        TaskSetEnabled_27c2a0(0, D_0045FCB8);
        TaskSetEnabled_27c2a0(0, D_0045F930);
        TaskSetEnabled_27c2a0(0, D_0045FAC8);
        TaskSetEnabled_27c2a0(0, D_0045FCC8);
        TaskSetEnabled_27c2a0(0, D_0045FB90);
        TaskSetEnabled_27c2a0(0, D_0045FBA0);
        TaskSetEnabled_27c2a0(1, D_0045FC60);
        return;
    case 5:
        TaskEnableBattleSet_2873f0();
        TaskSetEnabled_27c2a0(1, D_0045F9B8);
        TaskSetEnabled_27c2a0(1, D_0045FA18);
        TaskSetEnabled_27c2a0(1, D_0045FA60);
        TaskSetEnabled_27c2a0(1, D_0045FA78);
        TaskSetEnabled_27c2a0(1, D_0045FA88);
        TaskSetEnabled_27c2a0(0, D_0045FA28);
        TaskSetEnabled_27c2a0(0, D_0045FA98);
        TaskSetEnabled_27c2a0(0, D_0045FAA8);
        TaskSetEnabled_27c2a0(0, D_0045FAB8);
        TaskSetEnabled_27c2a0(0, D_0045F920);
        TaskSetEnabled_27c2a0(0, D_0045F940);
        TaskSetEnabled_27c2a0(0, D_0045F930);
        TaskSetEnabled_27c2a0(0, D_0045FA38);
        TaskSetEnabled_27c2a0(0, D_0045FA48);
        TaskSetEnabled_27c2a0(0, D_0045FAC8);
        TaskSetEnabled_27c2a0(0, D_0045FAD8);
        TaskSetEnabled_27c2a0(0, D_0045FAF0);
        TaskSetEnabled_27c2a0(0, D_0045FB10);
        TaskSetEnabled_27c2a0(0, D_0045FB30);
        TaskSetEnabled_27c2a0(0, D_0045F9D0);
        TaskSetEnabled_27c2a0(0, D_0045F9F0);
        TaskSetEnabled_27c2a0(0, D_0045FB48);
        TaskSetEnabled_27c2a0(0, D_0045FB60);
        TaskSetEnabled_27c2a0(0, D_0045FCD8);
        TaskSetEnabled_27c2a0(0, D_0045FCE8);
        TaskSetEnabled_27c2a0(0, D_0045FCF0);
        TaskSetEnabled_27c2a0(0, D_0045F998);
        TaskSetEnabled_27c2a0(0, D_0045FD00);
        TaskSetEnabled_27c2a0(0, D_0045FD10);
        TaskSetEnabled_27c2a0(0, D_0045FD20);
        TaskSetEnabled_27c2a0(0, D_0045FD30);
        TaskSetEnabled_27c2a0(0, D_0045FD40);
        TaskSetEnabled_27c2a0(0, D_0045FB80);
        TaskSetEnabled_27c2a0(0, D_0045FD50);
        TaskSetEnabled_27c2a0(0, D_0045FB90);
        TaskSetEnabled_27c2a0(0, D_0045FBA0);
        TaskSetEnabled_27c2a0(0, D_0045FBB0);
        TaskSetEnabled_27c2a0(0, D_0045FBC0);
        TaskSetEnabled_27c2a0(0, D_0045FBE0);
        TaskSetEnabled_27c2a0(0, D_0045FC00);
        TaskSetEnabled_27c2a0(0, D_0045FC20);
        TaskSetEnabled_27c2a0(0, D_0045FC40);
        TaskSetEnabled_27c2a0(0, D_0045FC60);
        TaskSetEnabled_27c2a0(0, D_0045F950);
        TaskMoveBefore_27bf50(D_0045F998, D_0045F9A8);
        TaskMoveBefore_27bf50(D_0045F9B8, D_0045F9A8);
        EffectReleaseCharaEffectsAllMaybe_27a210();
        GameSceneCBlurReset_2f1e20();
        SceneScreenOverlayResetMaybe_2f1ea0();
        TaskSetEnabled_27c2a0(0, D_0045FD70);
        TaskSetEnabled_27c2a0(0, D_0045FD40);
        MapMgrSlotsReleaseMotionEvents_1e15a0(((s32)GetMapMgr_201a90()));
        return;
    case 11:
        TaskEnableBattleSet_2873f0();
        TaskSetEnabled_27c2a0(1, D_0045FA60);
        TaskSetEnabled_27c2a0(1, D_0045FD80);
        TaskSetEnabled_27c2a0(0, D_0045FA98);
        TaskSetEnabled_27c2a0(0, D_0045FAA8);
        TaskSetEnabled_27c2a0(0, D_0045FAB8);
        TaskSetEnabled_27c2a0(0, D_0045FA28);
        TaskSetEnabled_27c2a0(0, D_0045F920);
        TaskSetEnabled_27c2a0(0, D_0045F940);
        TaskSetEnabled_27c2a0(0, D_0045F930);
        TaskSetEnabled_27c2a0(0, D_0045FA38);
        TaskSetEnabled_27c2a0(0, D_0045FAC8);
        TaskSetEnabled_27c2a0(0, D_0045FAD8);
        TaskSetEnabled_27c2a0(0, D_0045FAF0);
        TaskSetEnabled_27c2a0(0, D_0045FB10);
        TaskSetEnabled_27c2a0(0, D_0045FB30);
        TaskSetEnabled_27c2a0(0, D_0045F9D0);
        TaskSetEnabled_27c2a0(0, D_0045F9F0);
        TaskSetEnabled_27c2a0(0, D_0045FB48);
        TaskSetEnabled_27c2a0(0, D_0045FB60);
        TaskSetEnabled_27c2a0(0, D_0045FCD8);
        TaskSetEnabled_27c2a0(0, D_0045FCE8);
        TaskSetEnabled_27c2a0(0, D_0045FCF0);
        TaskSetEnabled_27c2a0(0, D_0045F998);
        TaskSetEnabled_27c2a0(0, D_0045FD00);
        TaskSetEnabled_27c2a0(0, D_0045FD10);
        TaskSetEnabled_27c2a0(0, D_0045FD20);
        TaskSetEnabled_27c2a0(0, D_0045FD30);
        TaskSetEnabled_27c2a0(0, D_0045FD70);
        TaskSetEnabled_27c2a0(0, D_0045FD40);
        TaskSetEnabled_27c2a0(0, D_0045FB80);
        TaskSetEnabled_27c2a0(0, D_0045FD50);
        TaskSetEnabled_27c2a0(0, D_0045FB90);
        TaskSetEnabled_27c2a0(0, D_0045FBA0);
        TaskSetEnabled_27c2a0(0, D_0045FBB0);
        TaskSetEnabled_27c2a0(0, D_0045FBC0);
        TaskSetEnabled_27c2a0(0, D_0045FC20);
        TaskSetEnabled_27c2a0(0, D_0045FC40);
        TaskSetEnabled_27c2a0(0, D_0045FC60);
        TaskSetEnabled_27c2a0(0, D_0045F950);
        TaskSetEnabled_27c2a0(1, D_0045FA48);
        EffectReleaseCharaEffectsAllMaybe_27a210();
        GameSceneCBlurReset_2f1e20();
        SceneScreenOverlayResetMaybe_2f1ea0();
        MapMgrSlotsReleaseMotionEvents_1e15a0(((s32)GetMapMgr_201a90()));
        CharaEffectGroupsSetPausedHiddenAll_27a260(0, 0, -1);
        h = ((s32)GetEffectMgr_2d9040());
        EffectGroupSetPaused_2e2c80(h, 0x3E8, 1);
        EffectGroupSetHidden_2e2bd0(h, 0x3E8, 1);
        EffectGroupSetPaused_2e2c80(h, 0x7D0, 1);
        EffectGroupSetHidden_2e2bd0(h, 0x7D0, 1);
        EffectGroupSetPaused_2e2c80(h, 0xBB8, 1);
        EffectGroupSetHidden_2e2bd0(h, 0xBB8, 1);
        ((struct Prof *)GetStatusEffect_2d9010())->m08 = 0;
        return;
    case 8:
        TaskEnableEventCharaSetMaybe_286b10();
        TaskSetRenderTasksEnabled_287b90(0);
        TaskSetEnabled_27c2a0(0, D_0045FB90);
        TaskSetEnabled_27c2a0(0, D_0045FBA0);
        TaskSetEnabled_27c2a0(0, D_0045FD70);
        TaskSetEnabled_27c2a0(0, D_0045FDA0);
        TaskSetEnabled_27c2a0(0, D_0045FDB0);
        TaskSetEnabled_27c2a0(0, D_0045FDC0);
        TaskSetEnabled_27c2a0(0, D_0045FDD0);
        TaskSetEnabled_27c2a0(0, D_0045FDE0);
        TaskSetEnabled_27c2a0(0, D_0045FDF0);
        TaskSetEnabled_27c2a0(0, D_0045FE10);
        TaskSetEnabled_27c2a0(0, D_0045FE28);
        TaskSetEnabled_27c2a0(0, D_0045FE38);
        TaskSetEnabled_27c2a0(0, D_0045FE38);
        TaskSetEnabled_27c2a0(1, D_0045FE48);
        TaskSetEnabled_27c2a0(1, D_0045FE58);
        return;
    case 9:
        TaskEnableEventCharaSetMaybe_286b10();
        TaskSetRenderTasksEnabled_287b90(0);
        TaskSetEnabled_27c2a0(1, D_0045FE48);
        TaskSetEnabled_27c2a0(1, D_0045FE58);
        return;
    case 6:
        TaskEnableEventCharaSetMaybe_286b10();
        TaskSetEnabled_27c2a0(1, D_0045FA28);
        TaskSetEnabled_27c2a0(1, D_0045FA38);
        TaskSetEnabled_27c2a0(1, D_0045FA48);
        return;
    case 10:
        TaskTableRestoreOrder_27bed0();
        TaskEnableEventSceneSetMaybe_286f40();
        TaskSetEnabled_27c2a0(1, D_0045FE70);
        TaskSetEnabled_27c2a0(1, D_0045FD50);
        TaskSetEnabled_27c2a0(1, D_0045FC60);
        /* fallthrough */
    default:
        return;
    }
}
