/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"
#pragma opt_dead_assignments off

class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void SetPosXYZ(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x84, a0, a1, a2); }
    
    
    
    void GetPos2(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x94, a0); }
    void GetTgt2(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x98, a0); }
    
    
    void GetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    void GetTgt(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
    u8 padC4[0xF0 - 0xC4];
    Vec4 xF0;                           /* 0xF0 */
    u8 pad100[0x15C - 0x100];
    u8 x15C[0x200 - 0x15C];             /* 0x15C */
    f32 x200;                           /* 0x200 */
    f32 x204;
    f32 x208;
    s32 x20C;
    u8 pad210[0x2A0 - 0x210];
    u8 x2A0;                            /* 0x2A0 */
    u8 pad2A1[0x2E1 - 0x2A1];
    u8 x2E1;                            /* 0x2E1 */
};

typedef struct {
    u8 pad0[0x1A];
    s16 x1A;
} G0C_003081e0;

typedef struct {
    u8 pad0[0x18E];
    s16 x18E;
} G18_003081e0;

typedef struct {
    u8 pad0[0xC];
    G0C_003081e0 *xC;
    u8 pad10[0x18 - 0x10];
    G18_003081e0 *x18;
} G_003081e0;

typedef struct {
    u8 pad0[0x3D8];
    s32 x3D8;
} E_003081e0;

extern "C" {
G_003081e0 *GetGameData_1fede0(void);
void *GetActionMgr_1fdb50(void);
E_003081e0 *ActionMgrFindById_233b50(void *, s32);
s32 CharaGetModelObj_2386f0(E_003081e0 *);
void CharaGetPos_2388a0(E_003081e0 *, Vec4 *);
void CharaGetRot_2388b0(E_003081e0 *, Vec4 *);
s32 CharaGetActionMode_213850(E_003081e0 *);
void ObjGetNthAttachPointPos_1ade20(s32, s32, s32, Vec4 *);
void VecMinMax_1cb570(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
s32 MapEvQueryCollTrisMaybe_1ff1e0(u8 *, s32, Vec4 *, s32);
s32 CollTriListCompact_1ca3e0(u8 *, s32);
f32 CharaGetWaterSurfaceYMaybe_238340(E_003081e0 *);
f64 dpmul(f64, f64);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
f32 VecLengthXZ_1cb490(Vec4 *);
f64 Atan2_129148(f64, f64);
f32 AngleWrap_1cbf30(f32);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
s8 CameraModeGetCurrent_309370(Cam *);
f32 PadGetAnalogLXNorm_183af0(void *);
f32 PadGetAnalogLYNorm_183a50(void *);
void CameraDecayPushOffsetMaybe_160490(Cam *);
s32 GetSysParamTable_1c6be0(void);
void CameraObjApplyInputMaybe_1619e0(Cam *, s32, Vec4 *, u8 *, s32);
s32 CharaGetGroundPos_2382d0(E_003081e0 *, Vec4 *);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
s32 MeshRaycastWrapper_16f610(u8 *, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
void CameraSetPresetParams_309100(void *, s32);
s32 MapEvCollectCollTrisNearMaybe_1ff130(u8 *, s32, Vec4 *, Vec4 *, s32, f32);
extern f32 D_0045B080[];
extern f64 D_0047D1A8;
extern f32 D_0047D7CC;
extern f32 D_0047D898;
extern f32 D_0047D7F8;
extern f32 D_0047D88C;
extern u8 D_004B2570[];
}

static inline f32 Abs(f32 x) { if (x < 0.0f) { return -x; } return x; }
static inline f32 Sgn(f32 x, f32 s) { if (s < 0.0f) { return -x; } return x; }
static inline f32 Scale(f64 x, f64 a, f64 b) { return (f32)((f64)x + dpmul(a, (f64)b)); }
#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" void CameraFollowLeaderStepMaybe_3081e0(Cam *self, s32 owner, Vec4 *off, s32 b, s32 c, Vec4 *push)
{
    u8 buf[0x6000] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x10 + sizeof(Vec4)) + (0x0 + sizeof(Vec4)) + (0x10) + (0x20)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec4) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    Vec4 tgt __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 ang __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    Vec4 c1 __attribute__((aligned(16)));
    Vec4 c0 __attribute__((aligned(16)));
    Vec4 w __attribute__((aligned(16)));
    Vec4 c2 __attribute__((aligned(16)));
    Vec4 hit __attribute__((aligned(16)));
    Vec4 h1 __attribute__((aligned(16)));
    Vec4 p0 __attribute__((aligned(16)));
    Vec4 p1 __attribute__((aligned(16)));
    Vec4 p2 __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    u8 buf2[0x6000] __attribute__((aligned(16)));
    Vec4 q0 __attribute__((aligned(16)));
    Vec4 q1 __attribute__((aligned(16)));
    Vec4 q2 __attribute__((aligned(16)));
    Vec4 h2 __attribute__((aligned(16)));
    G_003081e0 *g;
    E_003081e0 *e;
    s32 n;
    s32 rider;
    f32 base;
    f32 s;
    f32 lim;
    f32 len;
    f32 a;
    f32 bb;
    f32 dist;
    s32 i;
    s32 r;

    g = GetGameData_1fede0();
    e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), g->x18->x18E);
    n = 0;
    if (e == 0) {
        return;
    }
    rider = CharaGetModelObj_2386f0(e);
    ZERO(&ang, 0x10);
    self->GetPos(&pos);
    self->GetTgt(&tgt);
    CharaGetPos_2388a0(e, &at);
    CharaGetRot_2388b0(e, &ang);
    base = at.y;
    at.y += 25.0f;
    if (((short)CharaGetActionMode_213850(e)) == 7) {
        if (rider != 0) {
            ObjGetNthAttachPointPos_1ade20(rider, 0, 0, &at);
            at.y += 5.0f;
        }
    }
    VecMinMax_1cb570(&(*(Vec4 *)(rgp_blk1 + 0x0)), &(*(Vec4 *)(rgp_blk1 + 0x10)), &tgt, &pos);
    (*(Vec4 *)(rgp_blk1 + 0x0)).y = tgt.y + 80.0f;
    (*(Vec4 *)(rgp_blk1 + 0x10)).y = tgt.y - 20.0f;
    s = D_0045B080[0];
    {
        f32 dx = 1.5f * s;
        f32 dy = 3.0f * s;
        (*(Vec4 *)(rgp_blk1 + 0x10)).x -= dx;
        (*(Vec4 *)(rgp_blk1 + 0x10)).y -= dy;
        (*(Vec4 *)(rgp_blk1 + 0x10)).z -= dx;
        (*(Vec4 *)(rgp_blk1 + 0x0)).x += dx;
        (*(Vec4 *)(rgp_blk1 + 0x0)).y += dy;
        (*(Vec4 *)(rgp_blk1 + 0x0)).z += dx;
    }
    (*(Vec4 *)(rgp_blk1 + 0x10)).w = 1.0f;
    (*(Vec4 *)(rgp_blk1 + 0x0)).w = 1.0f;
    if (self->x2A0 == 0) {
        n = MapEvQueryCollTrisMaybe_1ff1e0(buf, 0x100, &(*(Vec4 *)(rgp_blk1 + 0x0)), -1);
        n = CollTriListCompact_1ca3e0(buf, n);
    }
    if (e->x3D8 & 0x10) {
        lim = CharaGetWaterSurfaceYMaybe_238340(e);
        lim = lim + D_0047D1A8 * s;
        base = lim;
        if (at.y < lim) {
            at.y = lim;
        }
    }
    if (at.y > tgt.y && !(e->x3D8 & 4) && !(e->x3D8 & 0x10)) {
        at.y = tgt.y + D_0047D7CC * (at.y - tgt.y);
    } else {
        at.y = *(f32 *)((u8 *)&tgt + 4) + D_0047D898 * (at.y - *(f32 *)((u8 *)&tgt + 4));
    }
    if (e->x3D8 & 0x10) {
        if (at.y < base) {
            at.y = base;
        }
    }
    self->SetPosXYZ(at.x, at.y, at.z);
    if (((short)CharaGetActionMode_213850(e)) == 6 || ((short)CharaGetActionMode_213850(e)) == 7) {
        c1 = self->xF0;
        VecSub_1cbd00(&c0, &tgt, &c1);
        len = VecLengthXZ_1cb490(&c0);
        a = AngleWrap_1cbf30((f32)Atan2_129148((f64)c0.x, (f64)c0.z) - ang.y);
        bb = a < 0.0f ? -a : a;
        if (!(bb <= D_0047D7F8)) {
            lim = Sgn(D_0047D7F8, a);
            s = AngleWrap_1cbf30(lim + ang.y);
            c0.x = len * Sinf_128fd0(s);
            c0.z = len * Cosf_128d30(s);
            VecSub_1cbd00(&c1, &tgt, &c0);
            self->xF0 = c1;
        }
    }
    if (CameraModeGetCurrent_309370(self) == 0) {
        a = Abs(PadGetAnalogLXNorm_183af0(D_004B2570));
        bb = Abs(PadGetAnalogLYNorm_183a50(D_004B2570));
        if (a > D_0047D88C || bb > D_0047D88C) {
            CameraDecayPushOffsetMaybe_160490(self);
        }
    }
    CameraObjApplyInputMaybe_1619e0(self, GetSysParamTable_1c6be0(), &ang, buf, n);
    self->GetPos(&pos);
    self->GetTgt(&tgt);
    if (CameraModeGetCurrent_309370(self) == 2 && !(g->xC->x1A & 1) && CharaGetGroundPos_2382d0(e, &w) != 0) {
        w.y += 30.0f;
        h1 = pos;
        h1.y = w.y;
        dist = VecDistance_13d3d0(&h1, &w);
        r = -1;
        for (i = 0; i < 6; i++) {
            VecSub_13be40(&c2, &pos, &w);
            VecNormalize_13bd90(&c2, &c2);
            if (dist < 35.0f * (f32)i) {
                VecScale_13be00(&c2, &c2, dist);
            } else {
                VecScale_13be00(&c2, &c2, 35.0f * (f32)i);
            }
            VecAdd_13be20(&c2, &c2, &w);
            c2.y = 60.0f + w.y;
            r = MeshRaycastWrapper_16f610(buf, n, &w, &c2, &hit, 1, 0);
            if (r >= 0) {
                break;
            }
        }
        if (self->x2E1 != 0) {
            if (r < 0) {
                self->x2E1 = 0;
                CameraSetPresetParams_309100(self->x15C, 0);
            }
        } else if (r >= 0) {
            self->x2E1 = 1;
            CameraSetPresetParams_309100(self->x15C, 1);
        }
    }
    if (off != 0) {
        self->GetTgt2(&p0);
        VecAdd_13be20(&p1, &p0, off);
        VecSub_13be40(&p2, &p0, &p1);
        VecNormalize_13bd90(&p2, &p2);
        VecScale_13be00(&p2, &p2, 4.0f);
        VecAdd_13be20(&p0, &p0, &p2);
        if (MeshRaycastWrapper_16f610(buf, n, &p0, &p1, &d, 1, 0) < 0) {
            self->xF0 = p1;
        }
    }
    if (push != 0) {
        n = MapEvCollectCollTrisNearMaybe_1ff130(buf2, 0x100, &(*(Vec4 *)(rgp_blk1 + 0x0)), &pos, -1, 100.0f);
        self->GetPos2(&q0);
        VecAdd_13be20(&q1, &q0, push);
        VecSub_13be40(&q2, &q0, &q1);
        VecNormalize_13bd90(&q2, &q2);
        VecScale_13be00(&q2, &q2, 4.0f);
        VecAdd_13be20(&q0, &q0, &q2);
        VecScale_13be00(&q2, &q2, -2.0f);
        VecAdd_13be20(&q1, &q1, &q2);
        if (MeshRaycastWrapper_16f610(buf2, n, &q0, &q1, &h2, 1, 0) < 0) {
            q2.x = self->x200;
            q2.y = self->x204;
            q2.z = self->x208;
            q2.w = 0.0f;
            VecAdd_13be20(&q2, &q2, push);
            self->x200 = q2.x;
            self->x204 = q2.y;
            self->x208 = q2.z;
            self->x20C = 0;
        }
    }
}
