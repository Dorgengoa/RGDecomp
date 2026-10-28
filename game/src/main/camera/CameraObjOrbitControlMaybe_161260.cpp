/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

typedef struct Prm {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
} Prm;

typedef struct In {
    f32 x0;
    f32 x4;
    s32 x8;
} In;

typedef struct Ch18 {
    u8 pad0[0x18E];
    s16 x18E;
} Ch18;

typedef struct Ch {
    u8 pad0[0x18];
    Ch18 *x18;
    u8 pad1C[4];
    s32 x20;
} Ch;

typedef struct Ev {
    s16 x0;
    s16 x2;
} Ev;

class Obj {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Prm * GetPrm(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Prm *, (void *, int, int, int), 0x48, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    void v60(f32 a0) { VCM(void, (void *, f32), 0x60, a0); }
    void v64(f32 a0) { VCM(void, (void *, f32), 0x64, a0); }
    
    
    
    
    
    
    
    
    void v88(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x88, a0); }
    
    void v90(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x90, a0); }
    
    
    
    void vA0() { VCM0(void, 0xA0); }
    
    
    
    void vB0() { VCM0(void, 0xB0); }
    
    f32 vB8() { return VCM0(f32, 0xB8); }
    u8 padC4[0xE0 - 0xC4];
    Vec4 xE0;
    Vec4 xF0;
    u8 pad100[0x108 - 0x100];
    s32 x108;
    u8 pad10C[0x1F8 - 0x10C];
    f32 x1F8;
    u8 pad1FC[4];
    Vec4 x200;
    u8 pad210[4];
    s32 x214;
    s32 x218;
    f32 x21C;
    u8 pad220[0x254 - 0x220];
    s32 x254;
};

extern "C" {
s32 AngleDiffSign_13c0d0(f32, f32, f32);
f32 AngleStepToward_13c150(f32, f32, f32, s32);
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
f32 VecLength_13d4a0(Vec4 *);
void VecAddInPlace_13e070(Vec4 *, Vec4 *);
s32 CameraCollideGroundMaybe_160500(Obj *, s32, s32, int);
s32 CameraFindClearYawMaybe_160730(Obj *, s32, s32, int);
s32 CameraSweepEyeCollisionMaybe_160c90(Obj *, s32, s32, int);
s32 MeshRaycastWrapper_16f610(s32, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
f32 PadGetAnalogRYNorm_183b90(void *);
Ch *GetGameData_1fede0(void);
s32 GetActionMgr_1fdb50(void);
s32 GetCharaResMgr_1fdb60(void);
Ev *CharaResFindById_1f0530(s32, s32);
void *ActionMgrFindById_233b50(s32, s32);
char *CharaGetCurActionName_2123d0(void *);
void CharaGetPos_2388a0(void *, Vec4 *);
s32 IsInBattle_288420(void);
s32 CharaSysGetEncounterIdMaybe_3a36d0(s32);
s32 strcmp(const char *, const char *);
extern char D_00458CE8[];
extern f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D7CC;
extern f32 D_0047D89C;
extern f32 D_00481118;
extern f32 D_0048111C;
extern u8 D_004B2570[];
s32 CameraObjOrbitControlMaybe_161260(Obj *self, In *in, Vec4 *pos, s32 arg3, s32 arg4);
}

s32 CameraObjOrbitControlMaybe_161260(Obj *self, In *in, Vec4 *pos, s32 arg3, s32 arg4)
{
    static s32 D_00481120;
    Vec4 v140 __attribute__((aligned(16)));
    Vec4 v130 __attribute__((aligned(16)));
    Vec4 save __attribute__((aligned(16)));
    Vec4 v110 __attribute__((aligned(16)));
    Vec4 v100 __attribute__((aligned(16)));
    Vec4 vF0 __attribute__((aligned(16)));
    Vec4 vE0 __attribute__((aligned(16)));
    Vec4 vD0 __attribute__((aligned(16)));
    Vec4 vC0 __attribute__((aligned(16)));
    Vec4 vB0 __attribute__((aligned(16)));
    Vec4 vA0 __attribute__((aligned(16)));
    Prm *prm;
    Vec4 *pe;
    Vec4 *pf;
    f32 len;
    f32 lim;
    f32 sc;
    f32 dy;
    f32 k;
    f32 a;
    f32 t;
    f32 f;
    s32 r;
    Ch *ch;
    void *h;
    Ev *ev;

    if (self->x108 == 0) {
        return -1;
    }
    prm = self->GetPrm((int)(long)(in), (int)(long)(pos), (int)(long)(arg3));
    self->v88(&v140);
    self->v90(&v130);
    VecAdd_13be20(&v130, &v130, &self->x200);
    pe = &self->xE0;
    pf = &self->xF0;
    save = self->xF0;
    VecAdd_13be20(pe, &v140, &v130);
    VecSub_13be40(&v110, pe, pf);
    v110.y = 0.0f;
    VecNormalize_13bd90(&v100, &v110);
    VEC4_ZERO(vF0);
    len = VecLength_13d4a0(&v110);
    if (len <= 0.0f) {
        v110.z = 1.0f;
        len = 1.0f;
        v100.z = 1.0f;
    }
    if (len < prm->x0) {
        if (self->x1F8 < 0.0f) {
            VecScale_13be00(&vF0, &v100, len - prm->x0);
        } else {
            if (self->x1F8 < len) {
                self->x1F8 = len;
            }
            VecScale_13be00(&vF0, &v100, len - self->x1F8);
        }
    } else {
        self->x1F8 = -1.0f;
    }
    if (!(len <= prm->x4)) {
        VecScale_13be00(&vF0, &v100, len - prm->x4);
    }
    lim = prm->x0;
    if (len < lim) {
        a = len;
    } else {
        a = lim;
    }
    sc = (in->x0 * lim) / a;
    if (sc != 0.0f) {
        self->v60(sc);
    }
    dy = in->x4;
    prm->x10 += dy;
    if (prm->x10 < prm->x18) {
        prm->x10 = prm->x18;
        D_00481120 = 1;
    }
    if (!(prm->x10 <= prm->x14)) {
        prm->x10 = prm->x14;
    }
    if (dy == 0.0f) {
        if (!(prm->x20 <= prm->x10)) {
            prm->x10 = prm->x10 + (prm->x20 - prm->x10) / D_00481118;
        }
        if (prm->x1C < prm->x10) {
            prm->x10 = prm->x10 + (prm->x1C - prm->x10) / D_00481118;
        }
    }
    t = (len - prm->x0) / (prm->x4 - prm->x0);
    vF0.y = prm->x8 + t * (prm->xC - prm->x8);
    pf->y = pe->y + prm->x10;
    k = (f32)self->x254 * -PadGetAnalogRYNorm_183b90(D_004B2570);
    if (D_00481120 != 0 && k < 0.0f) {
        VecScale_13be00(&vE0, &v100, 5.0f);
        VecAdd_13be20(&vF0, &vF0, &vE0);
        f = 0.5f * (10.0f * -k - D_0048111C);
        if (f != 0.0f) {
            if (!((f < 0.0f ? -f : f) <= 2.0f)) {
                f = 2.0f * (f / (f < 0.0f ? -f : f));
            }
            D_0048111C += f;
        }
        if (!(D_0048111C <= 10.0f)) {
            D_0048111C = 10.0f;
        }
    }
    if (!(k <= D_0047D89C)) {
        D_00481120 = 0;
    }
    if (D_00481120 == 0) {
        D_0048111C *= 0.5f;
    }
    VecAddInPlace_13e070(pf, &vF0);
    if (in->x8 != 0 && !(self->x214 & 0x40)) {
        f32 y = pos->y;
        self->x218 = 1;
        self->x21C = y - D_0047D1FC;
    }
    if (self->x218 != 0) {
        f = AngleStepToward_13c150(self->vB8(), self->x21C, 1.0f, 0);
        self->v64(f);
        if (AngleDiffSign_13c0d0(f, self->x21C, D_0047D7CC) == 0) {
            self->x218 = 0;
        }
    }
    if (sc != 0.0f || (self->x214 & 0x80)) {
        r = CameraSweepEyeCollisionMaybe_160c90(self, arg3, arg4, 0);
    } else {
        CameraFindClearYawMaybe_160730(self, arg3, arg4, 0);
        r = CameraSweepEyeCollisionMaybe_160c90(self, arg3, arg4, 0);
    }
    if (CameraCollideGroundMaybe_160500(self, arg3, arg4, 0) == 1) {
        D_00481120 = 1;
    }
    vD0.x = pe->x;
    vD0.y = pe->y - 5.0f;
    vD0.z = pe->z;
    vD0.w = 1.0f;
    vC0.x = pe->x;
    vC0.y = pe->y + D_0048111C;
    vC0.z = pe->z;
    vC0.w = 1.0f;
    if (MeshRaycastWrapper_16f610(arg3, arg4, &vD0, &vC0, &vB0, 1, 0) >= 0) {
        D_0048111C = vB0.y - pe->y;
        if (D_0048111C < 0.0f) {
            D_0048111C = 0.0f;
        }
    }
    f = D_0048111C;
    pe->y += f;
    pf->y -= f;
    ch = GetGameData_1fede0();
    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ch->x18->x18E);
    if (h != 0 && CharaGetCurActionName_2123d0(h) != 0 && strcmp(CharaGetCurActionName_2123d0(h), D_00458CE8) == 0) {
        self->xF0 = save;
    }
    if (((unsigned char)IsInBattle_288420()) != 0 && CharaSysGetEncounterIdMaybe_3a36d0(ch->x20) >= 0) {
        ev = CharaResFindById_1f0530(GetCharaResMgr_1fdb60(), 0x80);
        if (ev == 0) {
            goto end;
        }
        if (ev->x2 == 0x30EF) {
            goto hit;
        }
        if (ev->x2 != 0x30F0) {
            goto end;
        }
        {
        hit:
            if (h != 0) {
                CharaGetPos_2388a0(h, &vA0);
            }
            if (vA0.y < (f32)-0x125C) {
                self->xF0 = save;
            }
            if (self->xF0.y < (f32)-0x11F8) {
                self->xF0.y = (f32)-0x11F8;
            }
            if (self->xE0.y < (f32)-0x125C) {
                self->xE0.y = (f32)-0x125C;
            }
        }
    }
end:
    return r;
}
