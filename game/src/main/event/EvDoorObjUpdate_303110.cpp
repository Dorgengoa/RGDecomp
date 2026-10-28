/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Info {
    s32 x00;
    void *x04;
    s32 x08;
    s32 x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
} Info;

typedef struct Mtx {
    f32 m[16];
} Mtx;

typedef struct Part {
    u8 pad[0xC];
} Part;

typedef struct Chr {
    u8 pad000[0x30];
    s16 x30;
    u8 pad032[0x15C];
    s16 x18E;
} Chr;

typedef struct Game {
    u8 pad000[0x18];
    Chr *x18;
} Game;

struct Act {
    u8 pad000[0x10];
    u8 x010[0xC0];
    s32 flags;      /* 0xD0 */
    u8 pad0D4[0xC];
    u8 x0E0[0xA0];
    Part *x180;
    u8 pad184[4];
    s16 x188;
    u8 pad18A[2];
    u8 x18C[0x10];
    s16 x19C;
    s16 x19E;
    s8 x1A0;
    s8 x1A1;
    s8 x1A2;
    bool isX() { return (flags & 0x80000000) != 0; }
};

extern "C" {
void GameSceneDoorGlareStart_1cf7b0(void *);
void *GetCurrentScene_1f5be0(void);
void *GetActionMgr_1fdb50(void);
Game *GetGameData_1fede0(void);
void *ActionMgrFindById_233b50(void *, s32);
void CharaGetPos_2388a0(void *, Vec4 *);
s32 EventRecGetId_2e5710(Act *);
void XformGetScaledMatrix_2e76b0(u8 *, Mtx *, f32, f32, f32);
void EvObjUpdateBase_2f9910(Act *);
void EvScriptDispatchByNameAndId_2f9ab0(Act *, Info *, u8 *, s32);
s32 EvDoorObjGetSidePoint_3039a0(Act *, Vec4 *, Vec4 *, s32);
void EvDoorObjSetClosed_303bb0(Act *, s32);
void EvDoorObjPlayOpen_303c90(Act *, bool);
s32 EvDoorObjGetState_304040(Act *);
s32 EvDoorObjAnyRefAreaHasFlag80_304300(Act *);
bool EventRefListApplyPath_3044f0(Part *, Mtx *, u8 *, s32, bool);
void DoorCursorResetState_304a00(u8 *);
void DoorCursorShow_304a40(u8 *);
void DoorCursorSetPos_304a80(u8 *, Vec4 *);
s32 DoorCursorGetState_304a90(u8 *);
extern f32 D_0047F120;
extern f32 D_0047F124;
extern f32 D_0047F128;
extern f32 D_0047F12C;
void EvDoorObjUpdate_303110(Act *self);
}

void EvDoorObjUpdate_303110(Act *self) {
    Vec4 c __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Info info __attribute__((aligned(16)));
    Mtx m __attribute__((aligned(16)));
    Game *g;
    void *t;
    bool hit;
    bool nb;
    s32 v;
    s32 i;

    EvObjUpdateBase_2f9910(self);
    nb = !self->isX();
    if (!nb) {
        if (((short)EvDoorObjGetState_304040(self)) == 0) {
            return;
        }
        EvDoorObjSetClosed_303bb0(self, 0);
    }
    if (self->x1A2 == 0 && self->x1A1 != 0 && ((short)EvDoorObjGetState_304040(self)) == 0) {
        EvDoorObjPlayOpen_303c90(self, self->x1A0 != 0);
    }
    if (((short)DoorCursorGetState_304a90(self->x0E0)) == 0) {
        c.x = D_0047F120;
        c.y = D_0047F124;
        c.z = D_0047F128;
        c.w = D_0047F12C;
        g = GetGameData_1fede0();
        t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), g->x18->x18E);
        if (t != 0) {
            CharaGetPos_2388a0(t, &c);
        }
        if (EvDoorObjGetSidePoint_3039a0(self, &b, &c, g->x18->x30) != 0) {
            DoorCursorSetPos_304a80(self->x0E0, &b);
            DoorCursorShow_304a40(self->x0E0);
        }
    }
    if (self->x1A2 != 0) {
        if (self->flags & 0x2000000) {
            self->flags &= 0xBFFFFFFF;
            info.x00 = -1;
            info.x08 = 0;
            info.x0C = 0;
            info.x10 = 0;
            info.x14 = 0;
            info.x18 = 0;
            info.x1C = 0;
            info.x20 = 0;
            info.x04 = self;
            info.x00 = EventRecGetId_2e5710(self);
            EvScriptDispatchByNameAndId_2f9ab0(self, &info, self->x18C, self->x19E);
            if (((short)EvDoorObjGetState_304040(self)) == 1 && self->x19E == 0) {
                GameSceneDoorGlareStart_1cf7b0(GetCurrentScene_1f5be0());
            }
            XformGetScaledMatrix_2e76b0(self->x010, &m, 1.0f, 1.0f, 1.0f);
            hit = false;
            for (i = 0; i < self->x188; i++) {
                hit |= EventRefListApplyPath_3044f0(&self->x180[i], &m, self->x18C, self->x19E, self->x1A0 != 0);
            }
            if (!hit) {
                self->x1A2 = 0;
                switch (((short)EvDoorObjGetState_304040(self))) {
                case 1:
                    self->x19C = 2;
                    break;
                case 3:
                    self->x19C = 0;
                    self->flags |= 0x200;
                    break;
                }
            } else {
                self->x19E++;
            }
        }
    } else {
        self->x19E = 0;
        self->x1A2 = 0;
        if (((short)EvDoorObjGetState_304040(self)) == 2) {
            if ((u8)EvDoorObjAnyRefAreaHasFlag80_304300(self)) {
                v = self->flags | 0x100;
            } else {
                v = self->flags & ~0x100;
            }
            self->flags = v;
        }
    }
    if (((short)EvDoorObjGetState_304040(self)) != 0 && (self->flags & 0x200)) {
        DoorCursorResetState_304a00(self->x0E0);
    }
}
