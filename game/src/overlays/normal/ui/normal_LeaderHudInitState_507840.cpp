/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00507840 -- sibling of normal_LeaderHudReload_507990: same real C++
 * virtual dispatch through vtable slot 305 (offset 0x4CC = 8 + 4*305),
 * the jalr targets $25/$t9 exactly like normal_ShopMenuItemInfoShow_509520.cpp's
 * documented tell. Early "return 0" happens INSIDE the a1!=0 arm, before
 * the shared trailing "return 1" -- the nesting the retail control flow
 * actually has, not a flattening choice. */

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s305() { return VCM0(s32, 0x4CC); }
};

typedef struct Ctx {
    u8  pad000[0x18];
    s32 f18;
} Ctx;

/* Retail addresses this with a %hi/%lo pair (lui 0x4C / addiu -0x3DB0), which
   only a SYMBOL reference emits; the literal 0x4BC250 compiles to lui/ori.
   Spelling copied verbatim from normal_LeaderHudBuild_506dc0, a MERGED byte-identical
   unit on this image that references the SAME symbol. */
extern "C" u8 D_004BC250[];
extern "C" s32 D_0048456C;          /* gp - 0xC04 */
extern "C" s32 D_00484564;          /* gp - 0xC0C */
extern "C" s32 D_00484568;          /* gp - 0xC08 */
extern "C" s32 D_00484560;          /* gp - 0xC10 */
extern "C" s32 D_00484578;          /* gp - 0xBF8 */

extern "C" Ctx *GetGameData_1fede0(void);
extern "C" Obj *PartyGetLeaderChara_3c2820(s32 a0);
extern "C" s32  UiPageGetLayout_289b60(s32 a0);
extern "C" s32  UiPageGetList_289b50(s32 a0);
extern "C" s32  UiPageGetStateMachine_289b40(s32 a0);
extern "C" void UiSetWidgetVisible_290010(s32 p, s32 id, s32 c, s32 d);
extern "C" void UiFadeWidgetAlpha_290690(s32 p, s32 id, f32 x, f32 y, f32 z);
extern "C" void UiSetWidgetsVisibleById_291110(s32 p, s32 id, s32 c, s32 d);
extern "C" void StateMachineSetState_28ede0(s32 a0, s32 a1, s32 a2);
extern "C" void normal_LeaderHudWeaponFrameLayout_506850(s32 a0, s32 a1);
extern "C" void normal_LeaderHudWeaponRefresh_508990(void);
extern "C" void normal_LeaderHudGaugeLevelRefresh_507ff0(void);
extern "C" void normal_LeaderHudPanelSlideOffscreen_509140(s32 a0, s32 a1, s32 a2);
extern "C" void normal_LeaderHudBannerRefresh_507a30(void);
extern "C" s32  normal_LeaderHudGetBannerWidth_506ac0(s32 a0);
extern "C" void normal_LeaderHudBannerSlideEdge_507e90(s32 a0, s32 a1, s32 a2);
extern "C" void normal_LeaderHudBossGaugeRebuild_507170(void);

extern "C" s32 normal_LeaderHudInitState_507840(s32 a0, s32 a1);

s32 normal_LeaderHudInitState_507840(s32 a0, s32 a1)
{
    s32  tmp;
    s32  id;
    Ctx *ctx;
    Obj *obj;

    if (a1 != 0) {
        id = (s32)D_004BC250;
        D_0048456C = id;
        tmp = UiPageGetLayout_289b60(id);
        D_00484564 = tmp;
        tmp = UiPageGetList_289b50(D_0048456C);
        D_00484568 = tmp;
        tmp = UiPageGetStateMachine_289b40(D_0048456C);
        D_00484560 = tmp;
        UiSetWidgetVisible_290010(D_00484564, 1, 1, -1);
        UiFadeWidgetAlpha_290690(D_00484564, 1, 1.0f, 0.25f, 0.0f);
        normal_LeaderHudWeaponFrameLayout_506850(D_0048456C, 2);
        ctx = GetGameData_1fede0();
        if (ctx == 0) {
            return 0;
        }
        obj = PartyGetLeaderChara_3c2820(ctx->f18);
        if (obj != 0) {
            D_00484578 = obj->s305();
        } else {
            D_00484578 = -1;
        }
        normal_LeaderHudWeaponRefresh_508990();
        normal_LeaderHudGaugeLevelRefresh_507ff0();
        normal_LeaderHudPanelSlideOffscreen_509140(1, 1, 0);
        normal_LeaderHudBannerRefresh_507a30();
        UiSetWidgetsVisibleById_291110(D_00484564, 7, 0, 1);
        tmp = normal_LeaderHudGetBannerWidth_506ac0(D_0048456C);
        normal_LeaderHudBannerSlideEdge_507e90(tmp, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00484564, 7, 0, 1);
        normal_LeaderHudBossGaugeRebuild_507170();
        StateMachineSetState_28ede0(D_00484560, 0x59DA, 0);
    }
    return 1;
}
