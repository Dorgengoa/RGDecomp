#include "types.h"
#pragma optimization_level 3

struct Vec3 {
    f32 x, y, z;
};

struct Vec4 {
    f32 x, y, z, w;
};

struct QV {
    f32 x, y, z;
} __attribute__((aligned(16)));

struct Params {
    s32 x0;
    void *x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
};

struct Item {
    u8 pad[0x64];
};

struct Obj {
    u8 pad0[0x10];
    Vec3 m10[3];
    s32 w34[9];
    Vec3 m58[3];
    s32 w7C[9];
    u8 xA0[0x30];
    u32 flags;
    u8 padD4[0x110 - 0xD4];
    Item *items;
    s16 nitems;
    s16 pad116;
    u8 pad118[4];
    s32 x11C;
    u8 x120[0x10];
    s16 h130;
    s16 h132;
    bool IsDead() { return (flags & 0x80000000) != 0; }
};

extern "C" {
void EvObjUpdateBase_2f9910(Obj *);
void TargetRefApplyToEventObj_2e6810(u8 *, Vec3 *);
s32 ObjTypeVehicleGetPlayState_3380a0(Obj *);
u8 *GetMapMgr_201a90(void);
s32 TargetRefGetId_2e7120(u8 *);
u8 *MapSlotsFindById_1e4b90(u8 *, s32, s32);
s32 GetLoaderMgr_1f59d0(void);
s32 LoaderCountQueued_1cd620(s32);
s32 TargetRefGetMapObj_2e7050(u8 *);
s32 EventRecGetId_2e5710(Obj *);
void EvScriptDispatchByNameAndId_2f9ab0(Obj *, Params *, u8 *, s32);
void SrtCtor48_1c7510(Vec4 *);
bool EventPathEvalXformByName_2e3d20(s32, Vec4 *, u8 *, s32, s32);
void TargetRefDetachFromParent_2e5890(u8 *);
void TargetRefSetTranslation_2e5bf0(u8 *, Vec4 *);
void TargetRefSetRotation_2e5d10(u8 *, Vec4 *);
void EventObjSetPos_2e7230(Vec3 *, Vec4 *);
void EventObjSetRot_2e7240(Vec3 *, Vec4 *);
bool TargetRefPairAlignToNodeMaybe_338460(Item *, s32, u8 *, s32);
s32 GetCurrentScene_1f5be0(void);
void GameSceneSoundEnvSetLock_1d11a0(s32, s32);
}

extern "C" void ObjTypeVehicleUpdate_337520(Obj *self) {
    Params p;
    Vec4 c;
    Vec4 b;
    Vec4 a;
    s32 w;
    s32 *src;
    s32 *dst;
    s32 n;
    u8 *h;
    u8 *e;
    bool ok;
    s32 k;
    s32 i;
    bool live;
    f32 fx;
    f32 fy;
    f32 fz;


    EvObjUpdateBase_2f9910(self);
    live = !self->IsDead();
    if (!live || !(self->flags & 0x02000000)) {
        self->h130 = 0;
    } else {
        {
            fx = self->m10[0].x;
            fy = self->m10[0].y;
            fz = self->m10[0].z;
            self->m58[0].x = fx;
            self->m58[0].y = fy;
            self->m58[0].z = fz;
            fx = self->m10[1].x;
            fy = self->m10[1].y;
            fz = self->m10[1].z;
            self->m58[1].x = fx;
            self->m58[1].y = fy;
            self->m58[1].z = fz;
            fx = *(volatile f32 *)&self->m10[2].x;
            fy = self->m10[2].y;
            fz = self->m10[2].z;
            self->m58[2].x = fx;
            self->m58[2].y = fy;
            self->m58[2].z = fz;
            src = self->w34;
            dst = self->w7C;
            n = 9;
            do {
                n--;
                *dst = *src;
                src++;
                dst++;
            } while (n > 0);
            TargetRefApplyToEventObj_2e6810(self->xA0, self->m10);
            self->flags &= 0xBFFFFFFF;
            if (ObjTypeVehicleGetPlayState_3380a0(self) != 0) {
                h = GetMapMgr_201a90();
                e = MapSlotsFindById_1e4b90(h, TargetRefGetId_2e7120(self->xA0), 0);
                if (e != 0) {
                    *(u32 *)(e + 0x2C) |= 0x10;
                }
            }
            switch (ObjTypeVehicleGetPlayState_3380a0(self)) {
            case 1:
            case 3:
                break;
            default:
                return;
            }
            if (self->h132 == 0) {
                k = 0;
                switch (ObjTypeVehicleGetPlayState_3380a0(self)) {
                case 1:
                case 3:
                    k = LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0;
                    break;
                }
                if (k != 0) {
                    return;
                }
            }
            w = TargetRefGetMapObj_2e7050(self->xA0);
            p.x4 = 0;
            p.x0 = -1;
            p.x8 = 0;
            p.xC = 0;
            p.x10 = 0;
            p.x14 = 0;
            p.x18 = 0;
            p.x1C = 0;
            p.x20 = 0;
            p.x0 = EventRecGetId_2e5710(self);
            p.x4 = self;
            p.x8 = w;
            EvScriptDispatchByNameAndId_2f9ab0(self, &p, self->x120, self->h132);
            SrtCtor48_1c7510(&a);
            ok = EventPathEvalXformByName_2e3d20(self->x11C, &a, self->x120, self->h132, 0);
            TargetRefDetachFromParent_2e5890(self->xA0);
            TargetRefSetTranslation_2e5bf0(self->xA0, &c);
            TargetRefSetRotation_2e5d10(self->xA0, &b);
            EventObjSetPos_2e7230(self->m10, &c);
            EventObjSetRot_2e7240(self->m10, &b);
            for (i = 0; i < self->nitems; i++) {
                ok |= TargetRefPairAlignToNodeMaybe_338460(&self->items[i], w, self->x120, self->h132);
            }
            if (!ok) {
                k = GetCurrentScene_1f5be0();
                switch (ObjTypeVehicleGetPlayState_3380a0(self)) {
                case 1:
                    self->h130 = 2;
                    GameSceneSoundEnvSetLock_1d11a0(k, 0);
                    return;
                case 3:
                    self->h130 = 0;
                    GameSceneSoundEnvSetLock_1d11a0(k, 0);
                    return;
                }
            } else {
                self->h132++;
            }
        }
    }
}
