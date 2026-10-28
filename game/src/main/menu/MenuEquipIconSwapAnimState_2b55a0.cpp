/* rgp:protos */
#line 1
#pragma opt_lifetimes off
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f224() { return VCM0(u8 *, 0x388); }
    u8 * f225() { return VCM0(u8 *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f239() { return VCM0(u8 *, 0x3C4); }
    
    
    
    
    u8 * f244() { return VCM0(u8 *, 0x3D8); }
};

extern "C" {
void *GetGameData_1fede0(void);
f32 Sinf_128fd0(f32);
float PhaseAdvanceWrapPi_28b630(f32 *, f32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuItemIconSwapAnim_29b880(s32, s32, s32, s32, s32);
s32 *MenuGetMoveTarget_29f9e0(s32);
s32 MenuGetCursorIndex_29fa80(s32);
VObj *PartyGetSlotChara_3c2fb0(s32, s32);
extern f32 D_0047D3B8;
extern u16 D_0047ECE8[4];
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern f32 D_00482544;
s32 MenuEquipIconSwapAnimState_2b55a0(s32 arg0, s32 arg1);
}

s32 MenuEquipIconSwapAnimState_2b55a0(s32 arg0, s32 arg1)
{
    s32 x;
    s32 y;
    s32 g;
    s32 e;
    s32 a;
    s32 k;
    VObj *o;
    s32 p;
    s32 b;
    u8 *v;
    s32 *q;
    f32 f;
    s32 c;
    s32 n;

    if (arg1 != 0) {
        g = (s32)GetGameData_1fede0();
        o = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), MenuGetCursorIndex_29fa80(D_00482370));
        e = UiEntryListFindByTag_28ea40(D_00482364, 0x15);
        p = D_00482370 + 0x5C;
        a = *(s16 *)(e + 0x14) + *(s16 *)(e + 0x16) * 8;
        b = a + *(s16 *)(e + 0x1A) * 8;
        k = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
        k = *(s16 *)(k + 0x14) + *(s16 *)(k + 0x16) * 2;
        v = 0;
        if (k == 0) {
            v = o->f224();
        } else if (k == 1) {
            v = o->f225();
        } else if (k == 2) {
            v = o->f239();
        } else if (k == 3) {
            v = o->f244();
        }
        c = *(s16 *)(*(s32 *)(*(s32 *)((b << 2) + p + 0xA4) + 0x10) + 0x2C);
        n = -1;
        if (v != 0) {
            n = *(s16 *)(*(s32 *)(v + 0x10) + 0x2C);
        }
        MenuItemIconSwapAnim_29b880(D_00482370, n, c, k, a);
        UiSetWidgetsVisibleById_291110(D_00482360, (*(s16 *)(e + 0x14) + *(s16 *)(e + 0x16) * 8 + 0x166) & 0xFFFF, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, D_0047ECE8[k], 0, 1);
    }
    UiGetWidgetPos_2910a0(D_00482360, 0x17F, &x, &y);
    q = MenuGetMoveTarget_29f9e0(D_00482370);
    if (x == q[0] && y == q[1]) {
        StateMachineSetState_28ede0(D_0048235C, 0x64, 0);
    }
    e = UiEntryListFindByTag_28ea40(D_00482364, 0x15);
    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    f = 6.0f * Sinf_128fd0(D_00482544);
    UiMoveWidgetUniform_290f50(D_00482360, 0x186, (s32)(f + (f32)(*(s16 *)(e + 4) + 0x42 + *(s16 *)(e + 0x14) * *(s16 *)(e + 8))), (s32)(f + (f32)(*(s16 *)(e + 6) + 0x42 + *(s16 *)(e + 0x16) * *(s16 *)(e + 0xA))), 0.25f, 0);
    return 1;
}
