#include "types.h"

typedef unsigned __int128 u128;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4 __attribute__((aligned(16)));

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
    f32 pad;
} Vec3;

struct Cam {
    u8 pad000[0xC0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual void setRoll(f32);
};

typedef struct Obj {
    u8 pad000[0x170];
    f32 x170;
} Obj;

typedef struct Snd {
    u8 pad000[0x84];
    s32 x84;
    u8 pad088[4];
    s32 x8C;
} Snd;

extern "C" {
void ModelSetScale_150ff0(Obj *, Vec3 *);
void ModelSetRot_151080(Obj *, Vec3 *);
void CameraSetLag_177170(u8 *, f32, f32);
void ModelObjPlayMotionByName_1867a0(Obj *, void *, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
f32 GetSceneTimeStep_293350(void);
void MenuWeaponCombineInit_363400(Snd *, s32);
extern u8 D_00462D38[];
extern f32 D_0047D470;
extern f32 D_0047D5B0;
extern f32 D_0047D5B8;
extern f32 D_0047D610;
extern f32 D_0047F8A0;
extern f32 D_0047F8A4;
extern f32 D_0047F8B0;
extern f32 D_0047F8B4;
extern f32 D_0047F8B8;
extern f32 D_0047F8BC;
extern f32 D_0047F8C0;
extern f32 D_0047F8C4;
extern f32 D_0047F8C8;
extern f32 D_0047F8CC;
extern Snd *D_00482384;
extern s8 D_004823CC;
extern Obj *D_004823D0;
extern u8 *D_004823D4;
extern s32 D_00483038;
s32 MenuWeaponCombineOpenState_361330(void *arg0, s32 arg1);
}

s32 MenuWeaponCombineOpenState_361330(void *arg0, s32 arg1) {
    Vec4 v0;
    Vec4 v1;
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Obj *o;
    f32 f;
    u8 *p;
    u32 n;
    f32 t;

    if (arg1 != 0) {
        if (D_004823D4 != 0) {
            { f32 *p_v0 = (f32 *)&v0; p_v0[0] = D_0047F8B0; p_v0[1] = D_0047F8B4; p_v0[2] = D_0047F8B8; p_v0[3] = D_0047F8BC; }
            { f32 *p_v1 = (f32 *)&v1; p_v1[0] = D_0047F8C0; p_v1[1] = D_0047F8C4; p_v1[2] = D_0047F8C8; p_v1[3] = D_0047F8CC; }
            *(u128 *)(D_004823D4 + 0xE0) = *(u128 *)&v0;
            *(u128 *)(D_004823D4 + 0xF0) = *(u128 *)&v1;
            CameraSetLag_177170(D_004823D4, 1.0f, -1.0f);
            ((Cam *)D_004823D4)->setRoll(-1.0f);
        }
        if (D_004823D0 != 0) {
            D_004823CC = 1;
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462D38, 0);
            o = D_004823D0;
            p = (u8 *)&a;
            n = 16;
            if (p != 0) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            a.x = 0.0f;
            a.y = D_0047D5B0;
            a.z = 0.0f;
            ModelSetRot_151080(o, &a);
            o = D_004823D0;
            p = (u8 *)&b;
            n = 16;
            if (p != 0) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            b.x = D_0047D5B8;
            b.y = D_0047D5B8;
            b.z = D_0047D5B8;
            ModelSetScale_150ff0(o, &b);
            D_004823D0->x170 = D_0047D5B8;
        }
        D_00483038 = 0;
        D_0047F8A0 = D_0047D5B8;
        D_0047F8A4 = D_0047D5B8;
    }
    switch (D_00483038) {
    case 0:
        t = D_0047D610 * GetSceneTimeStep_293350();
        D_0047F8A0 = D_0047F8A0 + t;
        D_0047F8A4 = D_0047F8A4 + t;
        if (!(D_0047F8A0 <= 1.0f)) {
            D_0047F8A0 = 1.0f;
        }
        if (!(D_0047F8A4 <= 1.0f)) {
            D_0047F8A4 = 1.0f;
        }
        f = D_0047F8A0;
        o = D_004823D0;
        p = (u8 *)&c;
        n = 16;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        c.x = f;
        c.y = f;
        c.z = f;
        ModelSetScale_150ff0(o, &c);
        D_004823D0->x170 = D_0047F8A4;
        if (!(D_0047F8A0 < 1.0f) && !(D_0047F8A4 < 1.0f)) {
            D_00483038 = 1;
        }
        break;
    case 1:
        UiSetWidgetVisible_290010(D_00482384->x84, 0x1E7, 1, -1);
        MenuWeaponCombineInit_363400(D_00482384, 0);
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
