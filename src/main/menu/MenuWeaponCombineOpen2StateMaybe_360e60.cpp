#include "types.h"
#pragma opt_loop_invariants off

typedef unsigned int u128 __attribute__((mode(TI)));

struct Vec4 {
    f32 x, y, z, w;
};

struct IVec {
    s32 x;
    f32 y;
    s32 z;
    s32 w;
};

struct Base {
    u8 pad[0xC0];
};

struct Obj : public Base {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void Set(f32);
};

struct Snd {
    u8 pad[0x84];
    s32 x84;
    u8 pad88[4];
    s32 x8C;
};

extern "C" {
void ModelSetScale_150ff0(u8 *, Vec4 *);
void ModelSetRot_151080(u8 *, IVec *);
void CameraSetLag_177170(Obj *, f32, f32);
void ModelObjPlayMotionByName_1867a0(u8 *, void *, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
f32 GetSceneTimeStep_293350();
void MenuWeaponCombineInit_363400(Snd *, s32);
extern u8 D_00462D38[];
extern f32 D_0047D470;
extern f32 D_0047D5B0;
extern f32 D_0047D5B8;
extern f32 D_0047D610;
extern f32 D_0047F8A0;
extern f32 D_0047F8A4;
extern f32 D_0047F8D0;
extern f32 D_0047F8D4;
extern f32 D_0047F8D8;
extern f32 D_0047F8DC;
extern f32 D_0047F8E0;
extern f32 D_0047F8E4;
extern f32 D_0047F8E8;
extern f32 D_0047F8EC;
extern Snd *D_00482384;
extern s8 D_004823CC;
extern u8 *D_004823D0;
extern Obj *D_004823D4;
extern s32 D_00483038;
}

extern "C" s32 MenuWeaponCombineOpen2StateMaybe_360e60(s32 arg0, s32 arg1) {
    Vec4 a;
    Vec4 b;
    IVec c;
    Vec4 d;
    Vec4 e;
    u8 *p;
    u32 n;
    u8 *q;
    f32 v;
    Obj *o;
    f32 f;

    if (arg1 != 0) {
        o = D_004823D4;
        if (o != 0) {
            { f32 *pa = (f32 *)&a; pa[0] = D_0047F8D0; pa[1] = D_0047F8D4; pa[2] = D_0047F8D8; pa[3] = D_0047F8DC; }
            { f32 *pb = (f32 *)&b; pb[0] = D_0047F8E0; pb[1] = D_0047F8E4; pb[2] = D_0047F8E8; pb[3] = D_0047F8EC; }
            *(u128 *)((u8 *)o + 0xE0) = *(u128 *)&a;
            *(u128 *)((u8 *)o + 0xF0) = *(u128 *)&b;
            CameraSetLag_177170(o, 1.0f, -1.0f);
            D_004823D4->Set(-1.0f);
        }
        if (D_004823D0 != 0) {
            D_004823CC = 1;
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D38, 0);
            q = D_004823D0;
            p = (u8 *)&c;
            n = 16;
            if (p != 0) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            c.x = 0;
            c.z = 0;
            c.y = D_0047D5B0;
            ModelSetRot_151080(q, &c);
            q = D_004823D0;
            p = (u8 *)&d;
            n = 16;
            if (p != 0) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            v = D_0047D5B8;
            d.x = v;
            d.y = v;
            d.z = v;
            ModelSetScale_150ff0(q, &d);
            *(f32 *)(D_004823D0 + 0x170) = D_0047D5B8;
        }
        D_00483038 = 0;
        D_0047F8A0 = D_0047D5B8;
        D_0047F8A4 = D_0047D5B8;
    }
    switch (D_00483038) {
    case 0:
        f = D_0047D610 * GetSceneTimeStep_293350();
        D_0047F8A0 = D_0047F8A0 + f;
        D_0047F8A4 = D_0047F8A4 + f;
        if (!(D_0047F8A0 <= 1.0f)) {
            D_0047F8A0 = 1.0f;
        }
        if (!(D_0047F8A4 <= 1.0f)) {
            D_0047F8A4 = 1.0f;
        }
        v = D_0047F8A0;
        q = D_004823D0;
        p = (u8 *)&e;
        n = 16;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        e.x = v;
        e.y = v;
        e.z = v;
        ModelSetScale_150ff0(q, &e);
        *(f32 *)(D_004823D0 + 0x170) = D_0047F8A4;
        if (!(D_0047F8A0 < 1.0f) && !(D_0047F8A4 < 1.0f)) {
            D_00483038 = 1;
        }
        break;
    case 1:
        UiSetWidgetVisible_290010(D_00482384->x84, 0x1E7, 1, -1);
        MenuWeaponCombineInit_363400(D_00482384, 1);
        UiFadeWidgetAlpha_290690(D_00482384->x84, 0x1E7, 1.0f, 0.0625f, 0.0f);
        D_00483038 = 2;
        break;
    case 2:
        if (!(UiGetWidgetAlpha_290770(D_00482384->x84, 0x1E7) <= D_0047D470)) {
            StateMachineSetState_28ede0(D_00482384->x8C, 9, 0);
            D_00483038 = -1;
        }
        break;
    }
    return 1;
}
