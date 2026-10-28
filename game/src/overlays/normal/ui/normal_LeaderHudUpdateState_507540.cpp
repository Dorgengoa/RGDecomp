/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00507540 -- the book screen's per-frame driver.  The 00506b20 phase
 * selects the open / close / page-turn transitions, then the 00506b00 mode runs
 * the matching sub-screen, and finally the 0xBC hold-down counter is ticked and
 * the fade is retired when it reaches zero.
 *
 * C++ virtual: `lw $25,0x470($25)` -> slot (0x470-8)/4 = 282.
 * The four phase arms are laid out 0 / 3 / 2 / 1 in ADDRESS order, so that is
 * the SOURCE order -- mwcc builds the compare chain itself
 * (levers.d/m2c-switch-arm-order). */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s282() { return VCM0(s32, 0x470); }
};

typedef struct Bk  { u8 pad00[0xBC]; s32 fBC; } Bk;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern Bk   *D_0048456C;          /* gp - 0xC04 */

extern Ctx *GetGameData_1fede0(void);
extern Ent *PartyGetLeaderChara_3c2820(s32 w);
extern s32  UiPageWidgetAtTargetPos_2899b0(Bk *p, s32 id);
extern void UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern s32  normal_LeaderHudGetBannerWidth_506ac0(Bk *p);
extern void normal_LeaderHudSetBannerBlinking_506af0(Bk *p, s32 a);
extern s32  normal_LeaderHudGetPanelMode_506b00(Bk *p);
extern void normal_LeaderHudSetPanelMode_506b10(Bk *p, s32 a);
extern s32  normal_LeaderHudGetBannerPhase_506b20(Bk *p);
extern void normal_LeaderHudSetBannerPhase_506b30(Bk *p, s32 a);
extern s32  normal_LeaderHudGetField74Related_506b50(Bk *p);
extern void normal_LeaderHudBossGaugeUpdate_506fe0(void);
extern void normal_LeaderHudWeaponShakeStep_5072a0(void);
extern void normal_LeaderHudReload_507990(void);
extern void normal_LeaderHudBannerRefresh_507a30(void);
extern void normal_LeaderHudBannerSlide_507d70(s32 a, s32 b, s32 c);
extern void normal_LeaderHudGaugeLevelRefresh_507ff0(void);
extern void normal_LeaderHudWeaponRefresh_508990(void);
extern void normal_LeaderHudPanelSlide_509040(s32, s32);
}

extern "C" s32 normal_LeaderHudUpdateState_507540(void)
{
    Ctx *c;
    Ent *e;
    Bk  *p;
    s32 *q;

    normal_LeaderHudWeaponShakeStep_5072a0();
    switch (((signed char)normal_LeaderHudGetBannerPhase_506b20(D_0048456C))) {
    case 0:
        normal_LeaderHudBannerRefresh_507a30();
        break;
    case 3:
        if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 7) != 0) {
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 0);
        }
        break;
    case 2:
        if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 7) != 0) {
            normal_LeaderHudBannerRefresh_507a30();
            c = GetGameData_1fede0();
            if (c == 0) {
                return 0;
            }
            e = PartyGetLeaderChara_3c2820(c->f18);
            if (e == 0) {
                return 0;
            }
            if (e->s282() != 0) {
                normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 0);
                normal_LeaderHudBannerSlide_507d70(normal_LeaderHudGetBannerWidth_506ac0(D_0048456C), 1, 1);
            }
            UiFadeWidgetAlpha_290690(D_00484564, 7, 1.0f, 0.0625f, -1.0f);
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 3);
        }
        break;
    case 1:
        p = D_0048456C;
        q = &p->fBC;
        if (p->fBC == 0) {
            *q = 7;
        }
        break;
    }
    normal_LeaderHudBossGaugeUpdate_506fe0();
    if (((signed char)normal_LeaderHudGetPanelMode_506b00(D_0048456C)) == 0) {
        normal_LeaderHudWeaponRefresh_508990();
        normal_LeaderHudGaugeLevelRefresh_507ff0();
    } else if (((signed char)normal_LeaderHudGetPanelMode_506b00(D_0048456C)) == 3) {
        if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 2) != 0) {
            normal_LeaderHudSetPanelMode_506b10(D_0048456C, 0);
        }
    } else if (((signed char)normal_LeaderHudGetPanelMode_506b00(D_0048456C)) == 2) {
        if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 2) != 0) {
            normal_LeaderHudReload_507990();
        }
    } else if (((signed char)normal_LeaderHudGetPanelMode_506b00(D_0048456C)) == 1) {
        normal_LeaderHudPanelSlide_509040(((void)(normal_LeaderHudGetField74Related_506b50(D_0048456C)), 0), 0);
        normal_LeaderHudSetPanelMode_506b10(D_0048456C, 2);
    }
    p = D_0048456C;
    q = &p->fBC;
    if (p->fBC > 0) {
        *q = p->fBC - 1;
        p = D_0048456C;
        if (p->fBC <= 0) {
            normal_LeaderHudBannerSlide_507d70(normal_LeaderHudGetBannerWidth_506ac0(p), 0, 0);
            UiFadeWidgetAlpha_290690(D_00484564, 7, 0.0f, 0.0625f, -1.0f);
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 2);
            D_0048456C->fBC = 0;
        }
    }
    return 1;
}
