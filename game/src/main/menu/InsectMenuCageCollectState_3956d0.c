/* rgp:protos */
#define RGP_SELF_InsectMenuCageCollectState_3956d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s32 id;
    s32 v;
    u8 pad14[0xB0 - 0x14];
} Desc;

typedef struct {
    u8 pad0[0x10];
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8 pad20[8];
    s32 e;
    s32 f;
    u8 pad30[0x10];
} Rect;

typedef struct {
    u8 pad0[0x18];
    u8 *p18;
} Sub;

typedef struct {
    s32 id;
    Sub *sub;
} Ctx;

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
extern s32 D_004834F0;
extern s32 D_00483530;
extern s32 D_00483534;
extern u8 D_004B2570[0x400];
extern u8 D_004E95C0[0x400];
extern u8 D_004E95E0[0x400];

s32 InsectMenuCageCollectState_3956d0(s32 arg0, s32 arg1)
{
    Desc d1 __attribute__((aligned(16)));
    Desc d2 __attribute__((aligned(16)));
    Rect r __attribute__((aligned(16)));
    Ctx *c;
    s32 res;

    if (arg1 != 0) {
        c = ((Ctx *)GetSelectedInsectEntryMaybe_206ad0());
        if (c != 0) {
            MsgFormatParamsCtor_28aa00(&d1);
            d1.id = c->id;
            d1.v = *(s16 *)(c->sub->p18 + 2);
            MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0xB), &d1, 1);
            UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
        }
        MsgFormatParamsCtor_28aa00(&d2);
        d2.id = c->id;
        MsgFormat_28a9a0(D_00483534, InsectMenuMsgLookup_398200(5), &d2, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7534, D_00483534, 0);
        UiWindowFitInit_398170(&r, 0x7534);
        r.a = 0x3C;
        r.b = 0xC;
        r.c = 0x1C;
        r.d = 8;
        r.e = 0x200;
        r.f = 0x1C0;
        UiWindowFitToText_28d0c0(&r, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
    }
    res = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if (res == 1) {
        c = ((Ctx *)GetSelectedInsectEntryMaybe_206ad0());
        if (c == 0) {
            return 0;
        }
        CageRecUnplace_3d0a70((s32)c->sub);
        SelectedInsectEntryClearMaybe_397e80();
        StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
    }
    return 1;
}
