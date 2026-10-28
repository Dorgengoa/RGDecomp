/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_dead_assignments off
#pragma opt_propagation off
#pragma opt_pulloutconstants off

typedef rg_u128 u128;

struct Vec4 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

struct Mtx {
    Vec4 r[4];
};

struct Item60 {
    u8 pad[0x60];
};

struct Base {
    u8 pad[0xC0];
};

struct Cam : public Base {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetEye(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    void GetAt(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
    
    void SetEye(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xB0, a0); }
    u8 padC4[0x1C];
    Vec4 at;             /* 0xE0 */
    Vec4 eye;            /* 0xF0 */
    u8 pad100[0x154];
    s32 i254;            /* 0x254 */
    s32 i258;            /* 0x258 */
    u8 pad25C[0x44];
    u8 b2A0;             /* 0x2A0 */
    u8 pad2A1[0x3F];
    u8 b2E0;             /* 0x2E0 */
};

struct Sub18 {
    u8 pad[0x18E];
    s16 id;              /* 0x18E */
};

struct SubC {
    u8 pad[0x1A];
    s16 flags;           /* 0x1A */
};

struct P238 {
    u8 pad[0x168];
    s16 mode;            /* 0x168 */
};

struct Sub20 {
    u8 pad[0x238];
    P238 *p;             /* 0x238 */
};

struct Ctl {
    u8 pad0[0xC];
    SubC *c;             /* 0x0C */
    u8 pad10[8];
    Sub18 *s;            /* 0x18 */
    u8 pad1C[4];
    Sub20 *t;            /* 0x20 */
};

struct Obj4CC {
    u8 pad[0x4CC];
    f32 f4CC;
};

extern "C" {
Ctl *GetGameData_1fede0(void);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
s32 GetTargetMng_313dd0(void);
s32 TargetMngGetTargetRef_320820(s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void CharaGetRot_2388b0(s32, Vec4 *);
s32 PadIsTriggered_1839f0(void *, s32);
void OptionsSetCameraBitMaybe_3d6080(SubC *, s32);
void CameraResetParams_3090a0(Cam *);
s32 TargetRefIsActive_2e6f00(s32);
s32 TargetMngHasTargetId_313bf0(void);
void TargetRefGetPos_2e6a60(s32, Vec4 *);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void AxisAngleBetweenVecs_1d7da0(Vec4 *, f32 *, Vec4 *, Vec4 *);
void VecRotateAxisAngle_1d7f10(Vec4 *, Vec4 *, Vec4 *, f32);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
void CameraFollowLeaderStepMaybe_3081e0(Cam *, s32, s32, s32, s32, s32);
f32 PadGetAnalogRXNorm_183c30(void *);
f32 PadGetAnalogRYNorm_183b90(void *);
void VecSetLength_13e000(Vec4 *, Vec4 *, f32);
void MtxRotY_13ce20(Mtx *, f32);
void MtxMulVec4_13c900(Vec4 *, Mtx *, Vec4 *);
f32 sceVu0InnerProduct(Vec4 *, Vec4 *);
s32 TargetRefGetKind_2e7130(s32);
s32 TargetRefGetId_2e7120(s32);
Obj4CC *ObjRecGetLiveObject_1c4a90(s32, s32);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
f32 VecLength_13d4a0(Vec4 *);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f64 Acos_129130(f64);
f32 WrapAngle_13c050(f32);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void VecMinMax_1cb570(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
s32 MapEvQueryCollTrisMaybe_1ff1e0(Item60 *, s32, Vec4 *, s32);
s32 CollTriListCompact_1ca3e0(Item60 *, s32);
s32 CollSphereSweepNearest_1c8880(Vec4 *, Vec4 *, Item60 *, s32, s32, Vec4 *, Vec4 *, f32 *, f32);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
s32 MeshRaycastWrapper_16f610(Item60 *, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
s32 CharaGetCurActionName_2123d0(s32);
s32 strcmp(const char *, const char *);
f32 sqrtf(f32);
extern u8 D_004E72A8[];
extern u8 D_004E72A9[];
extern u8 D_004E72AA[];
extern bool D_004E7290[];
extern u128 D_004E7270;
extern u128 D_004E7280;
extern f32 D_004E7294[];
extern f32 D_004E7298[];
extern f32 D_004E729C[];
extern s32 D_004E72A0[];
extern s32 D_004E72A4[];
extern u8 D_004B2570[];
extern f32 D_0045B080[];
extern f32 D_0047D8E8;
extern f32 D_0047D7F8;
extern f32 D_0047D5D0;
extern f32 D_0047D278;
extern f32 D_0047D8EC;
extern f32 D_0047D84C;
extern f32 D_0047D8F0;
extern f32 D_0047D8F4;
extern f32 D_0047D8F8;
extern f32 D_0047D1FC;
extern f32 D_0047D310;
extern f32 D_0047D7CC;
extern f32 D_0047D7C4;
extern char D_00462240[];
}

extern "C" void CameraModeLockTargetUpdateMaybe_3062e0(Cam *c, s32 w) {
    f32 f3AC;
    f32 f3A8;
    f32 f3A4;
    f32 f3A0;
    f32 f39C;
    Vec4 pos __attribute__((aligned(16)));
    Vec4 v6370 __attribute__((aligned(16)));
    Vec4 v6360 __attribute__((aligned(16)));
    Vec4 eye2 __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    Vec4 v6330 __attribute__((aligned(16)));
    Vec4 v6320 __attribute__((aligned(16)));
    Vec4 q6310 __attribute__((aligned(16)));
    Vec4 d6300 __attribute__((aligned(16)));
    Vec4 d62F0 __attribute__((aligned(16)));
    Vec4 eye __attribute__((aligned(16)));
    Vec4 tgt __attribute__((aligned(16)));
    Vec4 v62C0 __attribute__((aligned(16)));
    Mtx m6280 __attribute__((aligned(16)));
    Vec4 v6270 __attribute__((aligned(16)));
    Vec4 v6260 __attribute__((aligned(16)));
    Vec4 v6250 __attribute__((aligned(16)));
    Vec4 q6240 __attribute__((aligned(16)));
    Vec4 v6230 __attribute__((aligned(16)));
    Vec4 v6220 __attribute__((aligned(16)));
    Vec4 q6210 __attribute__((aligned(16)));
    Vec4 v6200 __attribute__((aligned(16)));
    Vec4 v61F0 __attribute__((aligned(16)));
    Vec4 v61E0 __attribute__((aligned(16)));
    Vec4 v61D0 __attribute__((aligned(16)));
    Vec4 v61C0 __attribute__((aligned(16)));
    Vec4 v61B0 __attribute__((aligned(16)));
    Mtx m6170 __attribute__((aligned(16)));
    Vec4 v6160 __attribute__((aligned(16)));
    Vec4 v6150 __attribute__((aligned(16)));
    Vec4 q6140 __attribute__((aligned(16)));
    Vec4 v6130 __attribute__((aligned(16)));
    Vec4 v6120 __attribute__((aligned(16)));
    Vec4 v6110 __attribute__((aligned(16)));
    Item60 arr[0x100] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x10 + sizeof(Vec4)) + (0x0 + sizeof(Vec4)) + (0x10) + (0x20)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec4) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    Vec4 vE0 __attribute__((aligned(16)));
    Vec4 vD0 __attribute__((aligned(16)));
    Vec4 vC0 __attribute__((aligned(16)));
    Vec4 vb __attribute__((aligned(16)));
    Vec4 va __attribute__((aligned(16)));
    Vec4 hit __attribute__((aligned(16)));
    Ctl *ctl;
    s32 u;
    s32 id;
    s32 t;
    s32 fast;
    s32 flag;
    bool keep;
    bool ok;
    s32 n;
    s32 m;
    Obj4CC *o;
    P238 *p;
    s32 mode;
    f32 f26;
    f32 f25;
    f32 f24;
    f32 f23;
    f32 f22;
    f32 f21;
    f32 f20;
    f32 d;
    f32 e;
    f32 gb;
    f32 ga;

    ctl = GetGameData_1fede0();
    id = ctl->s->id;
    u = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (u == 0) return;
    t = TargetMngGetTargetRef_320820(GetTargetMng_313dd0());
    f25 = 120.0f;
    f23 = -1.0f;
    f20 = 35.0f;
    f21 = D_0047D8E8;
    f24 = 0.0f;
    fast = 1;
    if (D_004E72A8[0]) {
        f25 = 250.0f;
        f21 = f21 * 0.5f;
        f20 = 75.0f;
        fast = 0;
    }
    CharaGetPos_2388a0(u, &pos);
    pos.y = pos.y + 25.0f;
    CharaGetRot_2388b0(u, &v6370);
    c->GetEye(&eye2);
    c->GetAt(&at);
    flag = ctl->c->flags & 1;
    if (D_004E72AA[0] != 0) {
        if (fast != 0 && PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
            if (flag == 1) {
                OptionsSetCameraBitMaybe_3d6080(ctl->c, 0);
                CameraResetParams_3090a0(c);
            } else {
                OptionsSetCameraBitMaybe_3d6080(ctl->c, 1);
                D_004E7270 = 0;
                D_004E7280 = 0;
            }
        }
    } else {
        flag = 1;
    }
    if (flag == 0) {
        if (t != 0 && TargetRefIsActive_2e6f00(t) != 0 && ((unsigned char)TargetMngHasTargetId_313bf0()) != 0) {
            TargetRefGetPos_2e6a60(t, &v6360);
            VecSub_13be40(&v6330, &eye2, &at);
            v6330.y = 0.0f;
            VecNormalize_13bd90(&v6330, &v6330);
            VecSub_13be40(&v6320, &pos, &v6360);
            v6320.y = 0.0f;
            VecNormalize_13bd90(&v6320, &v6320);
            AxisAngleBetweenVecs_1d7da0(&q6310, &f3AC, &v6330, &v6320);
            if (D_0047D7F8 < f3AC) {
                f3AC -= D_0047D7F8;
                f3AC *= 0.5f;
                VecSub_13be40(&v6330, &eye2, &at);
                VecRotateAxisAngle_1d7f10(&v6330, &v6330, &q6310, f3AC);
                VecAdd_13be20(&eye2, &at, &v6330);
                c->SetEye(&eye2);
            }
        }
        CameraFollowLeaderStepMaybe_3081e0(c, w, 0, 0, 0, 0);
        return;
    }
    *(u128 *)&d6300 = D_004E7270;
    *(u128 *)&d62F0 = D_004E7280;
    keep = D_004E7290[0];
    f26 = (f32)c->i258 * PadGetAnalogRXNorm_183c30(D_004B2570);
    f22 = (f32)c->i254 * PadGetAnalogRYNorm_183b90(D_004B2570);
    VecSub_13be40(&eye2, &eye2, &d6300);
    VecSub_13be40(&at, &at, &d62F0);
    if (t != 0 && TargetRefIsActive_2e6f00(t) != 0 && ((unsigned char)TargetMngHasTargetId_313bf0()) != 0) {
        c->GetEye(&eye);
        c->GetAt(&tgt);
        TargetRefGetPos_2e6a60(t, &v6360);
        VecSub_13be40(&v62C0, &eye, &pos);
        VecSetLength_13e000(&v62C0, &v62C0, f25);
        MtxRotY_13ce20(&m6280, f26 * f21);
        MtxMulVec4_13c900(&v62C0, &m6280, &v62C0);
        VecAdd_13be20(&eye, &v62C0, &pos);
        VecSub_13be40(&v6270, &eye, &pos);
        VecNormalize_13bd90(&v6270, &v6270);
        VecSub_13be40(&v6260, &v6360, &pos);
        VecNormalize_13bd90(&v6260, &v6260);
        f21 = sceVu0InnerProduct(&v6270, &v6260);
        if (((short)TargetRefGetKind_2e7130(t)) == 4) {
            o = ObjRecGetLiveObject_1c4a90(w, ((short)TargetRefGetId_2e7120(t)));
            if (o != 0) f23 = D_0047D5D0 * o->f4CC;
        }
        if (0.0f < f21) c->b2E0 = 0;
        if (f21 < -0.5f) c->b2E0 = 1;
        VecScale_13be00(&d6300, &d6300, D_0047D278);
        VecSub_13be40(&v6250, &v6360, &pos);
        VecScale_13be00(&d62F0, &v6250, 0.5f);
        VecSub_13be40(&v6230, &eye, &pos);
        v6230.y = 0.0f;
        VecSub_13be40(&v6220, &pos, &tgt);
        v6220.y = 0.0f;
        VecNormalize_13bd90(&v6230, &v6230);
        VecNormalize_13bd90(&v6220, &v6220);
        AxisAngleBetweenVecs_1d7da0(&q6240, &f3A8, &v6230, &v6220);
        VecSub_13be40(&v6200, &pos, &eye);
        v6200.y = 0.0f;
        VecSub_13be40(&v6220, &tgt, &eye);
        v6220.y = 0.0f;
        VecNormalize_13bd90(&v6200, &v6200);
        VecNormalize_13bd90(&v6220, &v6220);
        AxisAngleBetweenVecs_1d7da0(&q6210, &f3A4, &v6200, &v6220);
        if ((q6240.y < 0.0f && 0.0f < q6210.y) || (q6210.y < 0.0f && 0.0f < q6240.y)) {
            f3A8 = f3A8 * 0.5f;
            if (D_0047D8EC < f3A8) f3A8 = D_0047D8EC;
            VecSub_13be40(&v6230, &eye, &pos);
            v6230.y = 0.0f;
            VecRotateAxisAngle_1d7f10(&v6230, &v6230, &q6240, f3A8);
            VecAdd_13be20(&eye, &pos, &v6230);
        } else {
            d = f3A4;
            d = (d < 0.0f) ? -d : d;
            if (D_0047D84C < d) {
                VecSub_13be40(&v61F0, &pos, &eye);
                v61F0.y = 0.0f;
                f25 = VecLength_13d4a0(&v61F0);
                VecSub_13be40(&v61F0, &pos, &tgt);
                v61F0.y = 0.0f;
                f21 = VecLength_13d4a0(&v61F0);
                d = f25 * Cosf_128d30(D_0047D8F0);
                f21 = Acos_129130(sqrtf(f21 * f21 - d * d) / f21);
                VecSub_13be40(&v6230, &eye, &pos);
                v6230.y = 0.0f;
                VecNormalize_13bd90(&v6230, &v6230);
                VecSub_13be40(&v6220, &tgt, &pos);
                v6220.y = 0.0f;
                VecNormalize_13bd90(&v6220, &v6220);
                e = Acos_129130(sceVu0InnerProduct(&v6230, &v6220));
                f3A8 = D_0047D8F4 - f21 - e;
                f3A8 *= 0.5f;
                if (D_0047D8EC < f3A8) f3A8 = D_0047D8EC;
                VecSub_13be40(&v6230, &eye, &pos);
                v6230.y = 0.0f;
                VecRotateAxisAngle_1d7f10(&v6230, &v6230, &q6240, f3A8);
                VecAdd_13be20(&eye, &pos, &v6230);
            }
        }
        VecSub_13be40(&eye2, &eye, &d6300);
        VecSub_13be40(&at, &tgt, &d62F0);
        if (0.0f < f23) {
            TargetRefGetPos_2e6a60(t, &v61D0);
            *(u128 *)&v61C0 = *(u128 *)&eye;
            v61D0.y = 0.0f;
            v61C0.y = 0.0f;
            VecSub_13be40(&v61E0, &v61C0, &v61D0);
            f21 = D_0047D8F8 * f23;
            if (400.0f < f21) f21 = 400.0f;
            if (VecLength_13d4a0(&v61E0) < f21) {
                VecSetLength_13e000(&v61E0, &v61E0, f21);
                VecAdd_13be20(&v61D0, &v61D0, &v61E0);
                v61D0.y = eye.y;
                VecSub_13be40(&d6300, &v61D0, &eye2);
            }
        }
        c->b2E0 = 0;
        keep = 1;
    } else {
        VecSub_13be40(&v61B0, &eye2, &pos);
        VecSetLength_13e000(&v61B0, &v61B0, f25);
        MtxRotY_13ce20(&m6170, f26 * f21);
        MtxMulVec4_13c900(&v61B0, &m6170, &v61B0);
        VecAdd_13be20(&eye2, &v61B0, &pos);
        if ((u8)keep == 0) {
            VecScale_13be00(&d6300, &d6300, 0.5f);
            VecScale_13be00(&d62F0, &d62F0, 0.5f);
        }
        keep = 0;
    }
    ok = 1;
    if (eye2.y < pos.y) eye2.y = pos.y;
    { f32 k_ = 15.0f; if (pos.y + k_ < eye2.y) eye2.y = eye2.y + 0.5f * (pos.y + k_ - eye2.y); }
    *(u128 *)&at = *(u128 *)&pos;
    VecAdd_13be20(&eye2, &eye2, &d6300);
    VecAdd_13be20(&at, &at, &d62F0);
    if (D_004E729C[0] + (pos.y + f20) < at.y) at.y = D_004E729C[0] + (pos.y + f20);
    f24 = f24 * 40.0f;
    if (!(f24 <= 10.0f)) f24 = 10.0f;
    eye2.y = eye2.y - f24;
    if (PadIsTriggered_1839f0(D_004B2570, 2) != 0 || (((unsigned char)TargetMngHasTargetId_313bf0()) != 0 && PadIsTriggered_1839f0(D_004B2570, 8) != 0)) {
        D_004E72A0[0] = 20;
    }
    if (D_004E72A0[0] > 0) {
        D_004E72A0[0] = D_004E72A0[0] - 1;
        VecSub_13be40(&v6160, &eye2, &at);
        v6160.y = 0.0f;
        VecNormalize_13bd90(&v6160, &v6160);
        f3A0 = WrapAngle_13c050(D_0047D1FC + v6370.y);
        v6150.x = Sinf_128fd0(f3A0);
        v6150.y = 0.0f;
        v6150.z = Cosf_128d30(f3A0);
        v6150.w = 1.0f;
        AxisAngleBetweenVecs_1d7da0(&q6140, &f3A0, &v6160, &v6150);
        if (f3A0 != 0.0f) {
            if (D_004E72A4[0] == 1) {
                D_004E72A4[0] = 0;
            } else {
                f3A0 = f3A0 * 0.5f;
            }
            if (D_0047D310 < f3A0) {
                VecSub_13be40(&v6160, &eye2, &at);
                VecRotateAxisAngle_1d7f10(&v6160, &v6160, &q6140, f3A0);
                VecAdd_13be20(&eye2, &at, &v6160);
            } else {
                D_004E72A0[0] = 0;
            }
        }
    }
    p = ctl->t->p;
    mode = p != 0 ? p->mode : 0;
    if (mode == 1) {
        c->GetEye(&v6130);
        eye2.x = v6130.x;
        eye2.z = v6130.z;
        c->GetAt(&v6130);
        at.x = v6130.x;
        at.z = v6130.z;
    }
    if (ok) {
        gb = D_004E7294[0];
        ga = D_004E7298[0];
        if (!(f22 <= D_0047D7CC)) {
            d = D_0047D7C4 * (80.0f * f22 - gb);
            if (!(d <= 8.0f)) d = 8.0f;
            if (d < -8.0f) d = -8.0f;
            gb = gb + d;
            *(u128 *)&v6120 = *(u128 *)&pos;
            v6120.y = eye2.y;
            { f32 r_ = VecDistance_13d3d0(&eye2, &v6120); d = 0.5f * ((r_ - 80.0f) * f22 - ga); }
            if (!(d <= 5.0f)) d = 5.0f;
            if (d < -5.0f) d = -5.0f;
            ga = ga + d;
        } else {
            gb = gb * 0.5f;
            ga = ga * 0.5f;
        }
        VecSub_13be40(&v6110, &pos, &eye2);
        VecNormalize_13bd90(&v6110, &v6110);
        VecScale_13be00(&v6110, &v6110, ga);
        VecAdd_13be20(&eye2, &eye2, &v6110);
        D_004E7294[0] = gb;
        at.y = at.y + gb;
        D_004E7298[0] = ga;
    }
    if (c->b2A0 == 0) {
        VecMinMax_1cb570(&(*(Vec4 *)(rgp_blk1 + 0x0)), &(*(Vec4 *)(rgp_blk1 + 0x10)), &pos, &eye2);
        f20 = D_0045B080[0];
        (*(Vec4 *)(rgp_blk1 + 0x10)).x = (*(Vec4 *)(rgp_blk1 + 0x10)).x - f20;
        (*(Vec4 *)(rgp_blk1 + 0x10)).y = (*(Vec4 *)(rgp_blk1 + 0x10)).y - f20;
        (*(Vec4 *)(rgp_blk1 + 0x10)).z = (*(Vec4 *)(rgp_blk1 + 0x10)).z - f20;
        (*(Vec4 *)(rgp_blk1 + 0x10)).w = 1.0f;
        (*(Vec4 *)(rgp_blk1 + 0x0)).w = 1.0f;
        (*(Vec4 *)(rgp_blk1 + 0x0)).x = (*(Vec4 *)(rgp_blk1 + 0x0)).x + f20;
        (*(Vec4 *)(rgp_blk1 + 0x0)).y = (*(Vec4 *)(rgp_blk1 + 0x0)).y + f20;
        (*(Vec4 *)(rgp_blk1 + 0x0)).z = (*(Vec4 *)(rgp_blk1 + 0x0)).z + f20;
        n = CollTriListCompact_1ca3e0(arr, MapEvQueryCollTrisMaybe_1ff1e0(arr, 0x100, &(*(Vec4 *)(rgp_blk1 + 0x0)), -1));
        VecSub_13be40(&vE0, &eye2, &pos);
        if (CollSphereSweepNearest_1c8880(&vD0, &vC0, arr, n, 0, &pos, &vE0, &f39C, 0.25f * f20) >= 0) {
            f39C = (f39C > 0.0f) ? f39C : 0.0f;
            f39C = (f39C < 1.0f) ? f39C : 1.0f;
            VecScale_1cbca0(&vE0, &vE0, f39C);
        }
        VecAdd_1cbdc0(&eye2, &pos, &vE0);
        vb.x = eye2.x;
        vb.y = 5.0f + eye2.y;
        vb.z = eye2.z;
        vb.w = 1.0f;
        va.x = eye2.x;
        va.y = eye2.y - 10.0f;
        va.z = eye2.z;
        va.w = 1.0f;
        if (MeshRaycastWrapper_16f610(arr, n, &vb, &va, &hit, 1, 0) >= 0) {
            eye2.y = 10.0f + hit.y;
        }
    }
    m = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ctl->s->id);
    ok = 1;
    if (m != 0 && CharaGetCurActionName_2123d0(m) != 0 && strcmp((const char *)CharaGetCurActionName_2123d0(m), D_00462240) == 0) {
        ok = 0;
    }
    if (D_004E72A9[0]) {
        if (pos.y < (f32)-4700) ok = 0;
        if (eye2.y < (f32)-4600) eye2.y = (f32)-4600;
        if (at.y < (f32)-4700) at.y = (f32)-4700;
    }
    if (ok) *(u128 *)&c->eye = *(u128 *)&eye2;
    *(u128 *)&c->at = *(u128 *)&at;
    D_004E7270 = *(u128 *)&d6300;
    D_004E7280 = *(u128 *)&d62F0;
    D_004E7290[0] = keep;
}
