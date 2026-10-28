/* rgp:protos */
#define RGP_SELF_InsectMenuPlacedInCageMsgState_396100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Big {
    u8 pad0[0xC];
    s32 fC;
    s32 f10;
    u8 pad14[0x9C];
} Big;

typedef struct Desc {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    u16 f30;
    u8 pad32[0xE];
} Desc;

typedef struct Hdr {
    u8 pad0[0x10];
    s16 *f10;
} Hdr;

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
extern f32 D_0047FF44;
extern s32 D_0047FF48;
extern s32 D_004834F0;
extern Hdr *D_0048351C;
extern f32 D_00483520;
extern f32 D_00483524;
extern s32 D_00483530;
extern s32 D_00483560;
extern u8 D_004B2570[];
extern u8 D_004E95C0[];
extern u8 D_004E95E0[];
extern f32 D_004504F0[][2];
extern f32 D_004504F4[][2];

s32 InsectMenuPlacedInCageMsgState_396100(s32 arg0, s32 arg1)
{
    Big big __attribute__((aligned(16)));
    Desc d __attribute__((aligned(16)));
    s32 r;
    s32 bx;
    s32 by;
    s32 k;
    f32 *p0;
    f32 *p1;

    if (arg1 != 0) {
        MsgFormatParamsCtor_28aa00(&big);
        big.fC = D_0047FF48;
        big.f10 = *D_0048351C->f10;
        MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(8), &big, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7534, D_00483530, 0);
        UiWindowFitInit_398170(&d, 0x7534);
        d.f14 = 0xC;
        d.f18 = 0x58;
        d.f1C = 8;
        d.f28 = 0x200;
        d.f2C = 0x1C0;
        d.f10 = 0x11D;
        d.f20 = 3;
        d.f30 |= 8;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        bx = 0x7A3;
        by = 0x812;
        D_00483520 = (f32)bx + D_004504F0[D_00483560][0];
        D_00483524 = (f32)by + D_004504F4[D_00483560][0];
        D_0047FF44 = 1.0f;
        PlayMenuSe_289ef0(0x23);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004E95C0, 0x7534, 1.0f);
    } else {
        r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(D_004E95E0);
        if (r == 1) {
            SelectedInsectEntryClearMaybe_397e80();
            StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
        }
    }
    return 1;
}
