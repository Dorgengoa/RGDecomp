/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} Seg2116B0;

typedef struct {
    s16 a;
    s16 b;
} HP2116B0;

typedef struct {
    f32 x, y, z, w;
} V4_2116B0;

typedef struct {
    Seg2116B0 s[6];
    V4_2116B0 v;
    HP2116B0 h[5];
    s32 w;
} __attribute__((aligned(16))) Blk2116B0;

typedef struct {
    u8 pad[0x110];
    Blk2116B0 b[2];
} T2116B0;

typedef struct {
    s16 a;
    s32 b;
    s32 c;
    union {
        s32 w;
        struct {
            u16 lo;
            u16 hi;
        } h;
    } u;
    s32 e;
} Rec2116B0;

class Q2116B0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v60() { VCM0(void, 0xF8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v120() { VCM0(void, 0x1E8); }
    
    
    
    
    
    
    
    
    
    void v130() { VCM0(void, 0x210); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v170() { VCM0(void, 0x2B0); }
    
    
    
    
    
    
    
    
    
    void v180() { VCM0(void, 0x2D8); }
    
    
    
    
    
    
    
    
    
    void v190() { VCM0(void, 0x300); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f282() { return VCM0(u8 *, 0x470); }
};

extern "C" {
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void SrtSetRotThunk_1c73d0(u8 *, f32, f32, f32);
extern void SrtSetPosFromVecThunk_1c7410(u8 *, void *);
extern void MatToRotPos_1cade0(void *, void *, void *);
extern void MatMulVec4Args_1cb7f0(void *, void *, f32, f32, f32, f32);
extern void VecNormalize_1cbb80(void *, void *);
extern u8 *GetActionMgr_1fdb50(void);
extern u8 *GetGameData_1fede0(void);
extern void CharaResetBattleStateMaybe_212f20(u8 *, s32);
extern void CharaStartActionByName_216d90(u8 *, void *, long long, f32);
extern u8 *ActionMgrFindById_233b50(u8 *, s32);
extern f32 CharaGetGroundY_238350(u8 *);
extern Blk2116B0 *CharaGetGroundTri_238410(u8 *, s32);
extern void CharaSetVelocityFromVec_238790(u8 *, void *);
extern void CharaSetRot_2387d0(u8 *, f32, f32, f32);
extern void CharaSetPosVec_2387e0(u8 *, void *);
extern void CharaGetSrtMatrix_2388c0(u8 *, void *);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetParamInt_2e0530(s32, void *, s32, s32);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern void TargetRefDetachFromParent_2e5890(void *);
extern s32 TargetRefGetMatrix_2e6870(void *, void *);
extern s32 TargetRefIsActive_2e6f00(void *);
extern s32 TargetRefGetMapObj_2e7050(void *);
extern u8 *TargetRefGetObjSlot_2e70e0(void *);
extern s32 TargetRefGetId_2e7120(void *);
extern s32 TargetRefGetKind_2e7130(void *);
extern void TargetRefClear_2e71d0(void *);
extern u8 *EvMapObjFindById_2e9810(s32, s32);
extern s32 EvMapObjThrowStart_3661f0(u8 *, s32, void *, s32, void *);
extern s32 EquipSlotGetRecId_3a0760(u8 *);
extern Q2116B0 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern u8 D_0045C920[];
extern u8 D_0045C930[];
extern u8 D_0045C950[];
extern u8 D_0045C960[];
extern u8 D_0045C970[];
extern u8 D_0045C980[];
extern u8 D_0045C9A0[];
extern u8 D_0045C9C0[];
extern u8 D_0045C9E0[];
extern s32 D_0047E600;
extern s32 D_0047E604;
extern s32 D_0047E608;
extern s32 D_0047E60C;
extern s32 D_0047E610;
extern s32 D_004BCB20[];
}

static inline s32 HasF(u8 *o, s32 m) {
    return (*(s32 *)(o + 0x3D8) & m) != 0;
}

extern "C" s32 CharaReleaseHeldTarget_2116b0(u8 *o, s32 flag, f32 x, f32 y, f32 z) {
    f32 v190[16] __attribute__((aligned(16)));
    f32 v180[4] __attribute__((aligned(16)));
    f32 v170[4] __attribute__((aligned(16)));
    f32 v130[16] __attribute__((aligned(16)));
    f32 v120[4] __attribute__((aligned(16)));
    Rec2116B0 rec __attribute__((aligned(16)));
    f32 vC0[16] __attribute__((aligned(16)));
    f32 vB0[4] __attribute__((aligned(16)));
    Rec2116B0 t90 __attribute__((aligned(16)));
    Rec2116B0 t70 __attribute__((aligned(16)));
    f32 v60[4] __attribute__((aligned(16)));
    u8 *pl;
    u8 *t;
    u8 *t8;
    f32 ang;
    Q2116B0 *q;
    u8 *r;
    s32 i;
    Blk2116B0 *src;
    s32 g;
    s32 s;
    u8 *str;
    s32 lo;
    s32 hi;

    if (TargetRefIsActive_2e6f00(o + 0x9DC) != 0) {
        TargetRefGetMatrix_2e6870(o + 0x9DC, v190);
        MatToRotPos_1cade0(v170, v180, v190);
        TargetRefDetachFromParent_2e5890(o + 0x9DC);
        switch (((short)TargetRefGetKind_2e7130(o + 0x9DC))) {
        case 2:
            pl = GetActionMgr_1fdb50();
            t = ActionMgrFindById_233b50(pl, ((short)TargetRefGetId_2e7120(o + 0x9DC)));
            if (t == 0) {
                break;
            }
            CharaResetBattleStateMaybe_212f20(t, 0);
            ang = *(f32 *)(o + 0x64);
            {
                u8 *p_ = (u8 *)v60;
                u32 n_ = 0x10;
                if (p_) {
                    while (n_) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            v60[0] = Sinf_128fd0(ang);
            v60[2] = Cosf_128d30(ang);
            CharaSetRot_2387d0(t, 0.0f, ang, 0.0f);
            SrtSetRotThunk_1c73d0(t, 0.0f, ang, 0.0f);
            { f32 c_ = v60[2]; f32 b_ = v60[1]; f32 a_ = v60[0];
            *(f32 *)(t + 0x450) = a_;
            *(f32 *)(t + 0x454) = b_;
            *(f32 *)(t + 0x458) = c_; }
            *(f32 *)(t + 0x45C) = 0.0f;
            VecNormalize_1cbb80(t + 0x450, t + 0x450);
            { f32 c_ = v60[2]; f32 b_ = v60[1]; f32 a_ = v60[0];
            *(f32 *)(t + 0x440) = a_;
            *(f32 *)(t + 0x444) = b_;
            *(f32 *)(t + 0x448) = c_; }
            *(f32 *)(t + 0x44C) = 0.0f;
            VecNormalize_1cbb80(t + 0x440, t + 0x440);
            CharaSetPosVec_2387e0(t, v180);
            SrtSetPosFromVecThunk_1c7410(t, v180);
            *(s32 *)(t + 0xA44) &= ~0x40;
            *(s32 *)(t + 0xB20) = -1;
            D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E600;
            q = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), *(s16 *)(o + 0x424));
            if (q != 0 && (r = q->f282()) != 0) {
                switch (EquipSlotGetRecId_3a0760(r)) {
                case 0x6F:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E604;
                    break;
                case 0x70:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E608;
                    break;
                case 0x32B:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E60C;
                    break;
                case 0x32C:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E610;
                    break;
                }
            }
            for (i = 0; i < 2; i++) {
                src = CharaGetGroundTri_238410(o, i);
                ((T2116B0 *)t)->b[i] = *src;
            }
            *(s32 *)(t + 0x3D8) &= ~1;
            *(s32 *)(t + 0x3D8) &= ~2;
            *(s32 *)(t + 0x3D8) = HasF(o, 4) ? (*(s32 *)(t + 0x3D8) | 4) : (*(s32 *)(t + 0x3D8) & ~4);
            *(s32 *)(t + 0x3D8) = HasF(o, 8) ? (*(s32 *)(t + 0x3D8) | 8) : (*(s32 *)(t + 0x3D8) & ~8);
            *(s32 *)(t + 0x3D8) &= ~0x10;
            *(s32 *)(t + 0x3D8) &= ~0x20;
            *(s32 *)(t + 0x3D8) &= ~0x40;
            *(s32 *)(t + 0x3D8) &= ~0x80;
            *(f32 *)(t + 0x3EC) = CharaGetGroundY_238350(o);
            *(f32 *)(t + 0x3E0) = v180[1] - *(f32 *)(t + 0x3EC);
            CharaGetSrtMatrix_2388c0(o, v130);
            MatMulVec4Args_1cb7f0(v120, v130, x, y, z, 0.0f);
            CharaSetVelocityFromVec_238790(t, v120);
            if (flag == 0) {
                CharaStartActionByName_216d90(t, D_0045C920, (long long)(0), 1.0f);
                *(s16 *)(t + 0xA36) = 0x16;
            } else {
                CharaStartActionByName_216d90(t, D_0045C930, (long long)(0), 1.0f);
                *(s16 *)(t + 0xA36) = 0x17;
                g = GetEffectMgr_2d9040();
                rec.u.w = 0;
                if (*(s16 *)(o + 0x424) != 4) {
                    EffectCreateByName_2e1020(&t90, g, D_0045C950, -1);
                    rec.a = t90.a;
                    rec.b = t90.b;
                    rec.c = t90.c;
                    rec.u.w = t90.u.w;
                    lo = t90.u.h.lo;
                    lo = (rec.u.h.lo & 0xFFFF0000) | lo;
                    hi = t90.u.h.hi;
                    hi = (rec.u.h.hi & 0xFFFF0000) | hi;
                    rec.u.h.lo = lo;
                    rec.u.h.hi = hi;
                    rec.e = t90.e;
                } else {
                    EffectCreateByName_2e1020(&t70, g, D_0045C960, -1);
                    rec.a = t70.a;
                    rec.b = t70.b;
                    rec.c = t70.c;
                    rec.u.w = t70.u.w;
                    lo = t70.u.h.lo;
                    lo = (rec.u.h.lo & 0xFFFF0000) | lo;
                    hi = t70.u.h.hi;
                    hi = (rec.u.h.hi & 0xFFFF0000) | hi;
                    rec.u.h.lo = lo;
                    rec.u.h.hi = hi;
                    rec.e = t70.e;
                }
                EffectSetId_2e0100(g, &rec, *(s16 *)(o + 0x424));
                EffectSetParamInt_2e0530(g, &rec, 0, 0);
                EffectSetParamInt_2e0530(g, &rec, 1, ((short)TargetRefGetId_2e7120(o + 0x9DC)));
            }
            *(s32 *)(t + 0xA44) |= 0x20;
            break;
        case 8:
            s = GetEventObjMgr_2d1960();
            t8 = EvMapObjFindById_2e9810(s, *(s32 *)(TargetRefGetObjSlot_2e70e0(o + 0x9DC) + 8));
            if (t8 == 0) {
                break;
            }
            CharaGetSrtMatrix_2388c0(o, vC0);
            MatMulVec4Args_1cb7f0(vB0, vC0, x, y, z, 0.0f);
            str = D_0045C970;
            q = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), *(s16 *)(o + 0x424));
            if (q != 0 && (r = q->f282()) != 0) {
                switch (EquipSlotGetRecId_3a0760(r)) {
                case 0x6F:
                    str = D_0045C980;
                    break;
                case 0x70:
                    str = D_0045C9A0;
                    break;
                case 0x32B:
                    str = D_0045C9C0;
                    break;
                case 0x32C:
                    str = D_0045C9E0;
                    break;
                }
            }
            EvMapObjThrowStart_3661f0(t8, TargetRefGetMapObj_2e7050(o + 0x9DC), vB0, *(s16 *)(o + 0x424), str);
            break;
        }
    }
    TargetRefClear_2e71d0(o + 0x9DC);
    return 1;
}
