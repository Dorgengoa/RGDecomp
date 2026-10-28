/* rgp:protos */
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/InsectMenuCaughtChoiceOpen_396b60.s and build/b_drafts/InsectMenuCaughtChoiceOpen_396b60.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_dead_assignments off

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * get(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

typedef struct Tmp {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xA0];
} Tmp;

extern "C" u8 *GetGameData_1fede0(void);
extern "C" void UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern "C" void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern "C" s32 UiEntryListFindDataByTag_28ec30(void *, s32);
extern "C" void InsectMenuTopWindowLayout_396ef0(s32);
extern "C" u8 *UiGetWidgetText_28f620(void *, s32, s32);
extern "C" s32 InsectMenuMsgLookup_398200(s32);
extern "C" void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern "C" void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern "C" s32 *GetSelectedInsectEntryMaybe_206ad0(void);
extern "C" void MsgFormatParamsCtor_28aa00(Tmp *);
extern "C" s32 ItemGetNamePtr_3d0d60(u8 *);
extern "C" void Sprintf_1343b8(char *, char *, s32, s32);
extern "C" void UiSetTextString_28f510(void *, s32, char *, s32);
extern "C" void UiSetTextCenteredX_28f300(void *, s32, s32, s32);
extern "C" void StreamPlayMwv_207340(s32, s32, f32);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" u8 D_004E95C0[];
extern "C" u8 D_004E95E0[];
extern "C" u8 D_004834F0;
extern "C" char *D_00483530;
extern "C" f32 D_0047DADC;
extern "C" char D_004642D8[];

extern "C" s32 InsectMenuCaughtChoiceOpen_396b60(s32 arg0, s32 arg1)
{
    Tmp t __attribute__((aligned(16)));
    u8 *g;
    u8 *p;
    s32 *q;
    u8 *e;
    u8 *r;
    VObj *v;

    g = GetGameData_1fede0();
    if (g == NULL) {
        return 0;
    }
    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_004E95C0, 0x7532, 1, -1);
        UiSetWidgetVisible_290010(D_004E95C0, 0x7533, 1, -1);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7533, 0xFE, 0xA6);
        InsectMenuTopWindowLayout_396ef0(UiEntryListFindDataByTag_28ec30(D_004E95E0, 0x7535));
        p = UiGetWidgetText_28f620(D_004E95C0, 0x7533, 0);
        if (p != NULL) {
            *(s32 *)(p + 0x4) = InsectMenuMsgLookup_398200(2);
            *(s32 *)(p + 0x14) = InsectMenuMsgLookup_398200(4);
        }
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7531, 1, 1);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7533, 1.0f, D_0047DADC, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7532, 1.0f, D_0047DADC, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7531, 1.0f, D_0047DADC, 0.0f);
    }
    q = GetSelectedInsectEntryMaybe_206ad0();
    if (q[0] > 0) {
        MsgFormatParamsCtor_28aa00(&t);
        *(s32 *)((u8 *)&t + 0xC) = q[0];
        e = (u8 *)q[1];
        if (e != NULL) {
            s16 id = *(s16 *)(*(u8 **)(e + 0x18) + 0x2);
            v = *(VObj **)(*(u8 **)(*(u8 **)(g + 0x8) + 0x40) + 0x8);
            r = v->get(id);
            if (r != NULL) {
                Sprintf_1343b8(D_00483530, D_004642D8, ItemGetNamePtr_3d0d60(e), *(s32 *)(r + 0xC));
            }
        }
        UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
        UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
        StreamPlayMwv_207340(0x324, 0, 1.0f);
    }
    StateMachineSetState_28ede0(&D_004834F0, 0x753B, 0);
    return 1;
}
