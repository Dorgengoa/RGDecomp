/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00507BB0 -- the 0xC / 0xD page-counter refresh.  Both counter
 * widgets are hidden, the active entity's slot-284 page total and slot-283
 * current page are read, and if the book has a scroll position the 0xD label is
 * placed and shown (plus the 0x7 arrow when the total is positive).  The
 * slot-282 "dirty" query drives the one-shot re-open and is latched into
 * D_00484584.
 *
 * C++ virtuals: 0x470/0x474/0x478 -> slots 282 / 283 / 284. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s282() { return VCM0(s32, 0x470); }
    s32 s283() { return VCM0(s32, 0x474); }
    s32 s284() { return VCM0(s32, 0x478); }
};

typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern void *D_0048456C;          /* gp - 0xC04 */
extern s32   D_00484584;          /* gp - 0xBEC */

extern Ctx *GetGameData_1fede0(void);
extern Ent *PartyGetLeaderChara_3c2820(s32 w);
extern void UiSetWidgetsVisibleById_291110(void *p, u16 id, s32 c, s32 d);
extern void UiSetWidgetPos_290f60(void *p, u16 id, s32 x, s32 y);
extern void UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void UiSetWidgetColor_2905b0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern s32  normal_LeaderHudGetBannerWidth_506ac0(void *p);
extern void normal_LeaderHudSetBannerCountdown_506ab0(void *p, s32 a);
extern void normal_LeaderHudSetBannerBlinking_506af0(void *p, s32 a);
extern void normal_LeaderHudGaugeBarSet_506630(void *p, s32 id, s32 c, s32 d, f32 x, f32 y);
extern void normal_LeaderHudBannerBlinkTick_507a90(void);
}

extern "C" s32 normal_LeaderHudBannerGaugeRefresh_507bb0(void)
{
    Ctx *c;
    Ent *e;
    s32  tot;
    s32  cur;
    s32  pos;

    UiSetWidgetsVisibleById_291110(D_00484564, 0xC, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00484564, 0xD, 0, 1);
    c = GetGameData_1fede0();
    if (c == 0) {
        return 0;
    }
    e = PartyGetLeaderChara_3c2820(c->f18);
    if (e == 0) {
        return 0;
    }
    tot = e->s284();
    cur = e->s283();
    pos = normal_LeaderHudGetBannerWidth_506ac0(D_0048456C);
    normal_LeaderHudGaugeBarSet_506630(D_0048456C, 0xD, 1, 0x66, (f32)cur, (f32)tot);
    if (pos != 0) {
        UiSetWidgetPos_290f60(D_00484564, 0xD, pos - 0x86, 0x26);
        UiSetWidgetsVisibleById_291110(D_00484564, 0xD, 1, 1);
        if (tot > 0) {
            UiFadeWidgetAlpha_290690(D_00484564, 7, 1.0f, 0.0625f, -1.0f);
        }
    }
    if (e->s282() == 0) {
        if (D_00484584 != 0) {
            normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 1);
            normal_LeaderHudSetBannerCountdown_506ab0(D_0048456C, 0x1E);
        }
    }
    UiSetWidgetColor_2905b0(D_00484564, 7, 1.0f, 1.0f, 1.0f, -1.0f);
    normal_LeaderHudBannerBlinkTick_507a90();
    D_00484584 = e->s282();
    return 1;
}
