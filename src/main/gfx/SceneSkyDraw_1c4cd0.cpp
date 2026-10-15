#include "types.h"

typedef unsigned __int128 u128;
typedef union V4 {
    u128 q;
    f32 f[4];
} V4;

typedef struct M4 {
    V4 r[4];
} M4;

typedef struct Big {
    u8 pad0[0x10];
    V4 x10;
    V4 x20;
    u8 pad30[0x1B8 - 0x30];
    s32 x1B8;
    s32 x1BC;
    u8 pad1C0[0x10];
} Big;

class Obj {
public:
    u8 pad0[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void v4(void *m);
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
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void v39(void *v);
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual f32 v45();
};

typedef struct Ctx {
    u8 pad0[0x4344];
    s32 x4344;
    u8 pad4348[4];
    s32 x434C;
    u8 pad4350[0x4380 - 0x4350];
    s32 x4380;
} Ctx;

typedef struct Ent {
    u8 pad0[0x200];
    s32 x200;
    f32 x204;
} Ent;

extern "C" {
void VecScale_13be00(void *, void *, f32);
void MapSkyDrawLayers_17e760(void *, void *, void *, void *, s32, void *, void *);
void MapSkyDrawHorizonBand_17ee60(void *, void *, void *, void *);
void TimeOfDayBlendLightSet_18cb10(Ent *, void *);
void TimeOfDaySkyWeights_18d530(Ent *, void *);
void TimeOfDayPhaseWeights_18d630(Ent *, void *);
s32 TimeOfDayPhase_18d890(Ent *);
void *ObjRecGetLiveObject_1c3a00(Ctx *, s32);
Obj *ObjRecGetLiveObject_1c3bc0(Ctx *, s32);
void SceneGetSunPosMirrored_1c4f80(Ctx *, void *);
void SceneGetSunPos_1c4fc0(Ctx *, void *);
Ent *ObjRecGetLiveObject_1c5250(Ctx *, s32);
void *memset(void *, s32, u32);

void SceneSkyDraw_1c4cd0(Ctx *arg0, s32 arg1) {
    V4 sp300;
    V4 sp2F0;
    V4 sp2E0;
    u8 sp2B0[0x30];
    u8 sp280[0x30];
    Big spB0;
    V4 spA0;
    V4 sp90;
    M4 sp50;
    void *r;
    Obj *obj;
    Ent *p;

    if (arg1 < 0) {
        r = ObjRecGetLiveObject_1c3a00(arg0, 1);
        if (r == NULL) {
            r = ObjRecGetLiveObject_1c3a00(arg0, 0);
        }
    } else {
        r = ObjRecGetLiveObject_1c3a00(arg0, arg1);
    }
    if (r == NULL) {
        return;
    }
    sp300.q = 0;
    obj = ObjRecGetLiveObject_1c3bc0(arg0, arg0->x4344);
    if (obj != NULL) {
        obj->v39(&sp300);
        sp300.f[3] = obj->v45();
    }
    if (arg0->x4380 == -1) {
        p = ObjRecGetLiveObject_1c5250(arg0, arg0->x434C);
    } else {
        p = ObjRecGetLiveObject_1c5250(arg0, arg0->x4380);
    }
    if (p == NULL) {
        return;
    }
    if (p->x200 == 0) {
        return;
    }
    sp300.f[1] += p->x204;
    spB0.x1BC = 0;
    spB0.x1B8 = 0;
    memset(&spB0, 0, 0x1D0);
    TimeOfDayBlendLightSet_18cb10(p, &spB0);
    TimeOfDayPhaseWeights_18d630(p, sp2B0);
    TimeOfDaySkyWeights_18d530(p, sp280);
    SceneGetSunPos_1c4fc0(arg0, &sp2F0);
    SceneGetSunPosMirrored_1c4f80(arg0, &sp2E0);
    spA0.q = spB0.x10.q;
    VecScale_13be00(&spA0, &spA0, 0.0078125f);
    spA0.f[3] = 1.0f;
    sp90.q = spB0.x20.q;
    VecScale_13be00(&sp90, &sp90, 0.0078125f);
    sp90.f[3] = 1.0f;
    obj->v4(&sp50);
    sp50.r[3].q = sp300.q;
    MapSkyDrawHorizonBand_17ee60(r, &sp50, &spA0, &sp90);
    MapSkyDrawLayers_17e760(r, &sp300, &sp2F0, &sp2E0, TimeOfDayPhase_18d890(p), sp2B0, sp280);
}

}
