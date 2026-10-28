/* rgp:protos */
#line 1
#include "types.h"

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x50); }
};

struct Elem {
    u8 pad0[0xc];
    s16 mC;
    u8 padE[6];
    s16 m14;
};

struct Timer {
    u8 pad0[8];
    s16 m8;
    u8 padA[6];
    s16 m10;
};

struct Ctx {
    u8 pad0[0x3c];
    s32 m3C;
};

extern "C" s32 PadIsTriggered_1839f0(u8 *, s32);
extern "C" void PlayMenuSe_289ef0(s32);
extern "C" s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
extern "C" Elem *UiEntryListFindByTag_28ea40(s32, s32);
extern "C" void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern "C" Timer *UiEntryListGetCurrentData_28ec60(s32);
extern "C" void StateMachineSetState_28ede0(s32, s32, s32);
extern "C" void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern "C" void UiSetWidgetSubItemValue_291250(s32, s32, s32, long long);
extern "C" VC_0 *MenuGetSelItem_2a02d0(Ctx *);

extern "C" f32 D_0047D978;
extern "C" f32 D_0047D97C;
extern "C" s32 D_0048470C;
extern "C" s32 D_00484710;
extern "C" s32 D_00484720;
extern "C" Ctx *D_00484740;
extern "C" u8 D_004B2570[];

extern "C" s32 TransMenuItemQuantitySelectState_37ce70(s32 pad0, s32 arg1)
{
    s32 h;
    s32 prev;
    s32 res;
    Timer *t;
    Elem *e;

    if (arg1 != 0) {
        h = MenuGetSelItem_2a02d0(D_00484740)->f();
        e = UiEntryListFindByTag_28ea40(D_00484720, 0xD);
        e->m14 = D_00484740->m3C;
        e->mC = h;
        UiEntryListSelectByTag_28ea90(D_00484720, 0xD, 0);
        UiSetWidgetSubItemValue_291250(D_00484710, 0x7616, 0, (long long)(D_00484740->m3C));
    }
    t = UiEntryListGetCurrentData_28ec60(D_00484720);
    prev = t->m10;
    res = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 1, 0);
    if (res == 1) {
        PlayMenuSe_289ef0(5);
        D_00484740->m3C = t->m10;
        StateMachineSetState_28ede0(D_0048470C, 0x29, 0);
    } else if (res == 2) {
        PlayMenuSe_289ef0(6);
        D_00484740->m3C = 0;
        StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7613, 0.0f, D_0047D978, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 1.0f, D_0047D97C, -1.0f);
    } else {
        if (*(s32 *)((u8 *)D_00484720+0x14)==1) {
            t->m10 += 10;
            if (t->m8 < t->m10) {
                t->m10 = t->m8;
            }
            UiSetWidgetSubItemValue_291250(D_00484710, 0x7616, 0, (long long)(t->m10));
        } else if (*(s32 *)((u8 *)D_00484720+0x14)==2) {
            t->m10 -= 10;
            if (t->m10 <= 0) {
                t->m10 = 1;
            }
            UiSetWidgetSubItemValue_291250(D_00484710, 0x7616, 0, (long long)(t->m10));
        }
    }
    if (prev != t->m10) {
        PlayMenuSe_289ef0(4);
    }
    return 1;
}
