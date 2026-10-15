#include "types.h"

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual s32 f();
};

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} Sub10;

typedef struct {
    u8 pad0[0x10];
    Sub10 *unk10;
} Res;

typedef struct {
    u8 pad0[8];
    s64 unk8;
    u8 pad10[0xC];
    s16 unk1C;
    s16 unk1E;
} Ent;

typedef struct {
    s32 unk0;
    u8 pad4[0xD];
    s8 unk11;
    u8 pad12[2];
    s32 unk14;
    u8 pad18[8];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[8];
    Res *unk34;
    u8 pad38[4];
    s32 unk3C;
} Obj;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Glob;

extern "C" {
extern Glob *GetGameData_1fede0(void);
extern void UiSetItemIconSprite_288490(Obj *, s32, s32, s32, s32, s32);
extern Ent *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern VC_0 *MenuGetSelItem_2a02d0(Obj *);
extern void MenuSetSelMode_2a4e20(Obj *, s32);
extern Res *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
}

extern "C" s32 MenuItemCellPickSetup_2a3bc0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    Res *res;
    s32 h;
    Ent *e;
    s32 idx;
    s32 a;
    s32 b;

    res = InvFindByCategoryIndex_3c86e0(GetGameData_1fede0()->unk18, arg0->unk14, arg0->unk11, arg4, arg5, 0);
    if (res == 0) {
        return 0;
    }
    MenuSetSelMode_2a4e20(arg0, arg0->unk14);
    idx = arg4 + arg5 * 8;
    h = UiFindWidget_290460(arg0->unk0, arg1);
    if (h == 0) {
        return 0;
    }
    UiSetItemIconSprite_288490(arg0, h, res->unk10->unk2C, 0x28, 0x2D, 1);
    e = UiGetWidgetSubItem_28f2b0(arg0->unk0, arg2, 0);
    if (e == 0) {
        return 0;
    }
    a = arg0->unk3C;
    if (a > 1) {
        e->unk8 = a;
        e->unk1C = 10;
        e->unk1E = 0x10;
    } else {
        e->unk1E = 0;
        e->unk1C = 0;
    }
    b = MenuGetSelItem_2a02d0(arg0)->f();
    e = UiGetWidgetSubItem_28f2b0(arg0->unk0, arg3, 0);
    if (e == 0) {
        return 0;
    }
    e += idx;
    arg0->unk20 = arg0->unk11;
    arg0->unk24 = idx;
    if (a == b) {
        arg0->unk28 = -1;
    } else {
        arg0->unk28 = b - a;
    }
    e->unk8 = b - a;
    if (e->unk8 < 2) {
        e->unk1E = 0;
        e->unk1C = 0;
    }
    arg0->unk34 = res;
    return 1;
}
