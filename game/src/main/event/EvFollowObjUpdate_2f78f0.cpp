/* rgp:protos */
#line 1
#include "types.h"

typedef struct { f32 m[12]; } Mtx34;
typedef struct { f32 m[16]; } Mtx44;
typedef struct { f32 x, y, z, w; } Vec4;

struct Eff {
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;   
       
       
       
      
    void setPos(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); }
     
    void setScale(f32 a0) { VCM(void, (void *, f32), 0x60, a0); }
    u8 pad0B4[0xFC];
    s32 x1B0;
    f32 x1B4;
    s32 x1B8;
    s32 x1BC;
    u8 pad1C0[0x470];
};

typedef struct Actor {
    u8 pad000[0x10];
    u8 x010[0x90];
    u8 x0A0[0x30];
    s32 flags;      /* 0xD0 */
    u8 pad0D4[0xC];
    u8 x0E0[0x30];
    s32 x110;
    u8 pad114[0x10];
    s32 x124;
    u8 x128[0x14];
    f32 x13C;
    s32 x140;
} Actor;

typedef struct Obj {
    u8 pad000[0x32];
    s16 x32;
} Obj;

typedef struct Tgt {
    u8 pad000[0x80];
    s32 x80;
    u8 pad084[0x32];
    s16 xB6;
} Tgt;

extern "C" {
void NodeGetTranslation_186650(Obj *, Vec4 *);
void SrtToMatrix_1c7450(Mtx34 *, Mtx44 *);
void SrtMatMul_1c7470(Mtx34 *, Mtx44 *, Mtx44 *);
void SrtCtor48_1c7510(Mtx34 *);
s32 GetGameMode_1f59c0(void);
s32 ProjectileCloneAndRegister_22e560(Eff *);
s32 IsInBattle_288420(void);
void EventPathEvalXformByName_2e3d20(s32, Mtx34 *, u8 *, s32, s32);
void TargetRefDetachFromParent_2e5890(u8 *);
void TargetRefSetMatrix_2e5950(u8 *, Mtx44 *);
void TargetRefResolve_2e5ed0(u8 *, s32);
void TargetRefApplyToEventObj_2e6810(u8 *, u8 *);
void TargetRefGetMatrix_2e6870(u8 *, Mtx44 *);
s32 TargetRefIsActive_2e6f00(u8 *);
Obj *TargetRefGetMapObj_2e7050(u8 *);
s32 TargetRefGetKind_2e7130(u8 *);
void EventObjSetFromMatrix_2e72f0(u8 *, Mtx44 *);
void EvObjUpdateBase_2f9910(void *);
s32 GetObjRefTable_313de0(void);
Tgt *HandleRegistryLookup_314aa0(s32, s32);
void ProjectileCtor_317eb0(Eff *, s32, s32, s32, f32);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
void EvFollowObjUpdate_2f78f0(Actor *arg0, f32 *arg1);
}

void EvFollowObjUpdate_2f78f0(Actor *arg0, f32 *arg1) {
    Mtx44 m760 __attribute__((aligned(16)));
    Mtx44 m720 __attribute__((aligned(16)));
    Mtx34 m6F0 __attribute__((aligned(16)));
    Mtx44 m6B0 __attribute__((aligned(16)));
    Mtx34 m680 __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    struct { u8 b[0x630]; } eff;
    Obj *obj;
    Tgt *tgt;
    f32 t;
    f32 k;

    EvObjUpdateBase_2f9910((void *)arg0);
    if (!(arg0->flags & 0x8000)) {
        return;
    }
    TargetRefApplyToEventObj_2e6810(arg0->x0A0, arg0->x010);
    TargetRefResolve_2e5ed0(arg0->x0E0, 0);
    if (((short)TargetRefGetKind_2e7130(arg0->x0E0)) != 0 && TargetRefIsActive_2e6f00(arg0->x0E0) == 0) {
        return;
    }
    arg0->flags &= 0xBFFFFFFF;
    if (((short)TargetRefGetKind_2e7130(arg0->x0E0)) == 0) {
        if (arg0->x110 != 0) {
            SrtCtor48_1c7510(&m6F0);
            EventPathEvalXformByName_2e3d20(arg0->x110, &m6F0, arg0->x128, arg0->x124, 0);
            SrtToMatrix_1c7450(&m6F0, &m720);
            TargetRefSetMatrix_2e5950(arg0->x0A0, &m720);
            EventObjSetFromMatrix_2e72f0(arg0->x010, &m720);
        } else {
            TargetRefGetMatrix_2e6870(arg0->x0A0, &m6B0);
            EventObjSetFromMatrix_2e72f0(arg0->x010, &m6B0);
        }
    } else {
        TargetRefGetMatrix_2e6870(arg0->x0E0, &m760);
        TargetRefDetachFromParent_2e5890(arg0->x0A0);
        if (arg0->x110 != 0) {
            SrtCtor48_1c7510(&m680);
            EventPathEvalXformByName_2e3d20(arg0->x110, &m680, arg0->x128, arg0->x124, 0);
            SrtMatMul_1c7470(&m680, &m760, &m760);
        }
        TargetRefSetMatrix_2e5950(arg0->x0A0, &m760);
        EventObjSetFromMatrix_2e72f0(arg0->x010, &m760);
    }
    arg0->x124++;
    if (arg0->flags & 0x800000) {
        t = arg0->x13C - *arg1;
        arg0->x13C = t;
        if (t < 0.0f) {
            arg0->flags |= 0x01000000;
        }
    }
    if (!(arg0->flags & 0x10000)) {
        return;
    }
    obj = TargetRefGetMapObj_2e7050(arg0->x0A0);
    if (obj == 0) {
        return;
    }
    if (obj->x32 == 0) {
        return;
    }
    tgt = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), arg0->x140);
    if (tgt != 0 && (tgt->x80 & 8)) {
        obj->x32 = 0;
        tgt->xB6 = 1;
        return;
    }
    if (((unsigned char)IsInBattle_288420()) == 0) {
        return;
    }
    if (GetGameMode_1f59c0() != 7) {
        return;
    }
    NodeGetTranslation_186650(obj, &pos);
    ProjectileCtor_317eb0((Eff *)&eff, 5, -1, 2, 1.0f);
    k = D_0045B080[0];
    ((Eff *)&eff)->setScale(1.5f * k);
    ((Eff *)&eff)->setPos(pos.x, pos.y, pos.z);
    ((Eff *)&eff)->x1B0 = 0;
    ((Eff *)&eff)->x1B8 = 0;
    ((Eff *)&eff)->x1BC = 0;
    ((Eff *)&eff)->x1B4 = 4.0f * k;
    arg0->x140 = ProjectileCloneAndRegister_22e560((Eff *)&eff);
    *(u8 **)((u8 *)&eff + 0xB0) = D_00471AA0;
}
