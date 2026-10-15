#pragma optimization_level 3
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef unsigned __int128 u128;
typedef union V4 {
    u128 q;
    f32 f[4];
} V4;

typedef struct Ent {
    void *a;
    void *b;
    s32 cnt;
} Ent;

typedef struct Elem {
    u8 pad[0x340];
} Elem;

typedef struct Obj {
    s32 x0;
    u8 pad4[0xC];
    Elem arr[6];
    Ent e[4];
} Obj;

s64 dpmul(s64, s64);
s32 dptoli(s64);
void VecScale_13be00(void *, void *, f32);
void VecAdd_13be20(void *, void *, void *);
f32 RandFloat_13c010(void);
f32 VecDistance_13d3d0(void *, void *);
void GuardEffectStart_2d53e0(Elem *, void *, void *);
void GuardEffectSetSpeedScale_2d54b0(Elem *, f32);
void InsectCageSePlay_3844b0(void *, s32);
s32 MenuObjSlotIsActive_3849d0(Ent *);
void MenuObjGetPosWithOffsetMaybe_385cf0(void *, void *, s32);
s64 dpadd(s64, s64);
s64 fptodp(f32);
extern f32 D_0047DA0C;
extern f32 D_0047DA38;
extern f32 D_0047DA3C;
extern f32 D_0047DA40;
extern s32 D_004832A0;

void MenuObjBattlePairSpawnSparkMaybe_385a30(Obj *arg0, s32 arg1) {
    V4 sp70;
    V4 sp60;
    V4 sp50;
    V4 sp40;
    void *b;
    s32 *p;
    Ent *e;
    V4 *v;
    f32 h;
    s32 t;

    if (MenuObjSlotIsActive_3849d0(&arg0->e[arg1]) == 0) {
        return;
    }
    e = (Ent *)((u8 *)arg0 + 0x1390) + arg1;
    b = e->b;
    MenuObjGetPosWithOffsetMaybe_385cf0(e->a, &sp70, 1);
    MenuObjGetPosWithOffsetMaybe_385cf0(b, &sp60, 1);
    if (2.5f < VecDistance_13d3d0(&sp70, &sp60)) {
        return;
    }
    p = &((Ent *)((u8 *)arg0 + 0x1390) + arg1)->cnt;
    if (--*p > 0) {
        return;
    }
    VecAdd_13be20(&sp50, &sp70, &sp60);
    h = 0.5f;
    v = &sp50;
    VecScale_13be00(v, v, h);
    sp40.q = 0;
    sp40.f[0] = D_0047DA38 - D_0047DA3C * RandFloat_13c010();
    sp40.f[1] = D_0047DA0C + D_0047DA40 * RandFloat_13c010();
    sp40.f[2] = D_0047DA38 - D_0047DA3C * RandFloat_13c010();
    sp40.f[3] = 1.0f;
    GuardEffectSetSpeedScale_2d54b0(&arg0->arr[arg0->x0], D_0047DA38 + D_0047DA0C * RandFloat_13c010());
    GuardEffectStart_2d53e0(&arg0->arr[arg0->x0], &sp50, &sp40);
    arg0->x0++;
    if (arg0->x0 >= 6) {
        arg0->x0 = 0;
    }
    *p = dptoli(dpmul((s64)0x404E0000 << 32, dpadd((s64)0x3FF00000 << 32, fptodp(1.5f * RandFloat_13c010()))));
    InsectCageSePlay_3844b0(&D_004832A0, 1);
}
