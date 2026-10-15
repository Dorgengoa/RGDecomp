#include "types.h"

extern "C" {

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Slot {
    s32 type;
    s32 flags;
    union {
        f32 f;
        s32 i;
    } v;
} Slot;

typedef struct Actor {
    u8 pad0[0x3D0];
    s64 x3D0;
    s32 x3D8;
} Actor;

typedef struct Tgt {
    u8 pad0[0x46];
    s16 x46;
} Tgt;

typedef struct Game {
    u8 pad0[0x10];
    s32 x10;
} Game;

typedef struct Ctl {
    u8 pad0[0xA8];
    s16 xA8;
    u8 padAA[0x2];
    s16 xAC;
    s16 xAE;
    s16 xB0;
    s16 xB2;
    s16 xB4;
    s16 xB6;
    s32 xB8;
    u8 padBC[0x14];
    Slot slot[8];
    u8 pad130[0xA];
    u8 x13A;
    u8 x13B;
    u8 pad13C[0xA];
    s16 x146;
    u8 pad148[0x29];
    u8 x171;
    u8 pad172[0x2];
    s16 x174;
    s16 x176;
    f32 x178;
    f32 x17C;
    f32 x180;
    f32 x184;
    f32 x188;
    u8 pad18C[0xE0];
    s32 x26C;
    u8 pad270[0x20];
    s32 x290;
} Ctl;

extern s64 dpmul(s64, s64);
extern void VecNormalize_13bd90(V4 *, V4 *);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern f32 WrapAngle_13c050(f32);
extern void FrameGetWorldPos_148f30(s32, V4 *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern s32 ScriptVmHasLabel_1768f0(Ctl *, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void AxisAngleBetweenVecs_1d7da0(V4 *, f32 *, V4 *, V4 *);
extern void VecRotateAxisAngle_1d7f10(V4 *, V4 *, V4 *, f32);
extern s32 GetCurrentScene_1f5be0(void);
extern Game *GetGameData_1fede0(void);
extern void CharaSetYaw_2138f0(Actor *, f32);
extern s32 CharaGetId_214a80(Actor *);
extern Tgt *CharaGetWallTriMaybe_238390(Actor *, s32);
extern void CharaAddReqMove_238730(Actor *, V4 *);
extern void CharaGetForwardVec_238830(Actor *, V4 *);
extern void CharaGetPos_2388a0(Actor *, V4 *);
extern void CharaGetRot_2388b0(Actor *, V4 *);
extern void AiMoveToTargetChara_2bee40(Ctl *, Actor **);
extern void AiMoveToTargetPoint_2c0560(Ctl *, Actor **);
extern f32 CollTriMaxY_2c0d80(Tgt *);
extern void AiSetMoveTimedOut_2c1200(Ctl *, s32);
extern s32 AiIsNoTimeout_2c1230(Ctl *);
extern s32 AiIsMoveTimedOut_2c1240(Ctl *);
extern s32 AiScriptRunEntry_2c1550(void *, s32, s32);
extern s32 AiScriptResume_2c15f0(void *, s32);
extern s32 StateVarGet_3ccac0(s32, u8);
extern f32 dptofp(s64);
extern s64 fptodp(f32);
extern f32 D_0047DA8C;
extern f32 D_0047DADC;

}

extern "C" void AiUpdate_2c05b0(Ctl *self, Actor **pa) {
    f32 ang;
    V4 pos;
    V4 up;
    V4 d0;
    V4 d1;
    V4 d2;
    V4 d3;
    V4 rot;
    V4 axis;
    V4 vel;
    s32 w;
    Game *g;
    s32 id;
    Actor *o;
    bool ok;
    Tgt *t;
    s32 e;
    s32 m;
    s32 r;
    s32 i;
    Slot *s;

    w = GetCurrentScene_1f5be0();
    g = GetGameData_1fede0();
    if (pa != 0) {
        self->xA8 = CharaGetId_214a80(*pa);
    }
    if (pa != 0 && *pa != 0) {
        self->x171 = 0;
        if (self->x146 > 0) {
            self->x146--;
        }
        if (self->x174 > 0) {
            s16 c = self->x174 - 1;
            self->x174 = c;
            if (c == 0) {
                self->xAC = 600;
            }
        }
        id = CharaGetId_214a80(*pa);
        o = *pa;
        if (o != 0) {
            CharaGetPos_2388a0(o, &pos);
        }
        ok = false;
        if ((o->x3D8 & 0x40) && (o->x3D8 & 1)) {
            t = CharaGetWallTriMaybe_238390(o, 0);
            if (t != 0 && (t->x46 & 0x20)) {
                if (100.0f + pos.y > CollTriMaxY_2c0d80(t) && 0.0f <= self->x180) {
                    if (self->x176 < 5) {
                        self->x176++;
                    }
                    if (self->x178 <= 0.0f && self->x176 == 4) {
                        self->x178 = self->x180;
                        self->x188 = 0.0f;
                    }
                    ok = true;
                }
            }
        }
        if (!ok) {
            self->x176 = 0;
        }
        if (0.0f < self->x178) {
            up.y = self->x178;
            up.w = 1.0f;
            up.x = 0.0f;
            up.z = 0.0f;
            CharaAddReqMove_238730(o, &up);
            if (0.0f < self->x178) {
                self->x184 += self->x178;
            }
            if (120.0f < self->x184 || !(o->x3D8 & 0x40)) {
                self->x178 -= self->x17C;
            }
        }
        if (self->x178 <= 0.0f && 0.0f < self->x184 && !(o->x3D8 & 0x40)) {
            self->x188 += D_0047DADC;
        }
        if (self->x178 <= 0.0f && (o->x3D8 & 1)) {
            self->x178 = 0.0f;
            self->x184 = 0.0f;
        }
        if ((self->xB8 & 0x100) && !(o->x3D8 & 1)) {
            e = ObjRecGetLiveObject_1c4a90(w, self->x26C);
            if (e != 0) {
                m = ModelGetRootFrame_1511a0(e);
                if (m != 0) {
                    CharaGetForwardVec_238830(o, &d0);
                    CharaGetPos_2388a0(o, &d2);
                    FrameGetWorldPos_148f30(m, &d3);
                    VecSub_13be40(&d1, &d3, &d2);
                    d1.y = 0.0f;
                    VecNormalize_13bd90(&d1, &d1);
                    d0.y = 0.0f;
                    VecNormalize_13bd90(&d0, &d0);
                    AxisAngleBetweenVecs_1d7da0(&axis, &ang, &d0, &d1);
                    if (axis.y < 0.0f) {
                        ang *= -1.0f;
                    }
                    ang = 0.5 * ang;
                    if (ang > D_0047DA8C) {
                        ang = D_0047DA8C;
                    }
                    CharaGetRot_2388b0(o, &rot);
                    rot.y = WrapAngle_13c050(rot.y + ang);
                    CharaSetYaw_2138f0(o, rot.y);
                    if (ang != 0.0f) {
                        VecRotateAxisAngle_1d7f10(&d1, &d0, &axis, ang);
                        VecScale_13be00(&d1, &d1, 2.0f);
                        CharaAddReqMove_238730(o, &d1);
                    }
                }
            }
        }
        e = ObjRecGetLiveObject_1c4a90(w, id);
        if ((self->xB8 & 1) && e != 0) {
            u8 k = self->x13A;
            if ((s32)k >= 0) {
                r = StateVarGet_3ccac0(g->x10, k);
                if (r != self->x13B && r >= 0) {
                    s16 n = r + 0x6E;
                    self->xAC = n;
                    self->xB4 = n;
                }
                self->x13B = r;
            }
            if (self->xAC >= 0) {
                if (ScriptVmHasLabel_1768f0(self, self->xAC) != 0) {
                    AiScriptRunEntry_2c1550(self, self->xAC, id);
                    if (self->xAC == 100) {
                        self->xB6 = 1;
                    }
                    self->xAE = self->xAC;
                    self->xAC = -1;
                    self->xB8 |= 2;
                    self->x180 = -1.0f;
                } else {
                    self->xAC = -1;
                }
            }
            if (self->xAE >= 0 && (self->xB8 & 2) && AiScriptResume_2c15f0(self, id) != 0) {
                self->xAC = 200;
                self->xB8 &= ~2;
                self->x180 = -1.0f;
            }
            if (self->xB8 & 4) {
                if (self->xB0 >= 0) {
                    self->xB2 = self->xB0;
                    if (AiScriptRunEntry_2c1550((u8 *)self + 0x54, self->xB0, id) != 1) {
                        self->xB2 = -1;
                    }
                    self->xB0 = -1;
                }
                if (self->xB2 >= 0 && AiScriptResume_2c15f0((u8 *)self + 0x54, id) != 0) {
                    self->xB2 = -1;
                }
            }
        }
        if (AiIsMoveTimedOut_2c1240(self) == 0) {
            if (self->x184 <= 0.0f &&
                ((id >= 0 && id < 12) || (o->x3D8 & 0x10) || (o->x3D8 & 1) ||
                 (o->x3D0 & ((s64)0x80000 << 32)))) {
                if (self->xB8 & 0x10) {
                    AiMoveToTargetChara_2bee40(self, pa);
                    self->xB8 &= ~0x10;
                } else if (self->xB8 & 0x20) {
                    AiMoveToTargetPoint_2c0560(self, pa);
                    self->xB8 &= ~0x20;
                }
            } else if ((self->xB8 & 0x10) || (self->xB8 & 0x20)) {
                CharaGetForwardVec_238830(o, &vel);
                VecScale_13be00(&vel, &vel, self->x188);
                CharaAddReqMove_238730(o, &vel);
                self->xB8 &= ~0x10;
                self->xB8 &= ~0x20;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        if (self->slot[i].flags & 1) {
            switch (self->slot[i].type) {
            case 0:
                self->slot[i].v.i += 1;
                break;
            case 1:
                self->slot[i].v.f += 1.0f;
                break;
            }
        }
    }
    if (--self->x290 < 0) {
        self->x290 = 0;
        AiSetMoveTimedOut_2c1200(self, 1);
    }
    if (AiIsNoTimeout_2c1230(self) != 0) {
        AiSetMoveTimedOut_2c1200(self, 0);
    }
}
