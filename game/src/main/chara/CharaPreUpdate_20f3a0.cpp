/* rgp:protos */
#line 1
#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class Chr {
public:
    VC_VPTR_MEMBER;                                                                                                                                               
              
    bool Busy(s32 a0) { return (vc_u8)VCM(vc_u32, (void *, s32), 0x274, a0) != 0; }
                                                                      
    u8 * Slot(s32 a0) { return VCM(u8 *, (void *, s32), 0x384, a0); }
};

class Thing {
public:
    VC_VPTR_MEMBER;                                             
    s32 Check() { return VCM0(s32, 0xC0); }
};

typedef struct {
    __extension__ unsigned long long lo : 37;
    unsigned long long b37 : 1;
    unsigned long long mid : 18;
    unsigned long long b56 : 1;
    unsigned long long hi : 7;
} __attribute__((aligned(8))) Bits;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern "C" {
extern u8 *MapFindBlockAtPos_1e3a00(s32, Vec *, f32);
extern u8 *MapGetActiveArea_1e56e0(s32);
extern s32 MapDataIsLoaded_1e79d0(u8 *);
extern s32 MapDataGetId_1e7bd0(u8 *);
extern u8 *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern void ActCfgTableRunEvntByName_21f680(s32, s32, u8 *);
extern s32 ActCfgTableFindAbltByName_222870(s32, u8 *);
extern s32 ActInfoAbltGetKind_22ec20(s32);
extern void CharaSnapshotMotionMaybe_236c50(u8 *);
extern void CharaGetPos_2388a0(u8 *, Vec *);
extern s32 TargetRefResolve_2e5ed0(u8 *, s32);
extern void TargetRefGetPos_2e6a60(u8 *, Vec *);
extern s32 TargetRefGetId_2e7120(u8 *);
extern s32 TargetRefGetKind_2e7130(u8 *);
extern Chr *CharaMgrPoolFindById_3a8c60(s32, s32);
extern Thing *ActorFindById_3eb870(u8 *, s32);
extern u8 D_0045C758[];
extern u8 D_0045C768[];
extern u8 D_0045C798[];
extern u8 D_0045C7A8[];
extern u8 D_0045C7B8[];
extern u8 D_0045C7C8[];
}

#define S16(o) (*(s16 *)(p + (o)))
#define S32(o) (*(s32 *)(p + (o)))
#define U32(o) (*(u32 *)(p + (o)))
#define F32(o) (*(f32 *)(p + (o)))
#define BITS (*(Bits *)(p + 0x3D0))

extern "C" void CharaPreUpdate_20f3a0(u8 *p) {
    Vec v __attribute__((aligned(16)));
    Vec pos __attribute__((aligned(16)));
    s32 old;
    Chr *c;
    u8 *r;
    s32 w;
    s16 t;
    u8 *gm;
    Thing *o;
    s32 m;
    s32 unit;
    u8 *e;
    u32 f;
    bool b;
    u64 m64;
    f32 fx;
    f32 fy;
    f32 fz;

    S16(0xA3A) = S16(0xA32);
    S16(0xA3E) = S16(0xA34);
    S16(0xA3C) = S16(0xA36);
    S16(0xA40) = S16(0xA38);
    *(u64 *)(p + 0x560) = *(u64 *)(p + 0x568);
    old = S16(0xA2C);
    S16(0xA2C) = 0;
    S32(0x42C) = 0;
    S16(0xB44) = -1;
    S16(0xB46) = -1;
    c = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), S16(0x424));
    if (c != 0) {
        r = c->Slot(0);
        if (r != 0) {
            S16(0xB44) = *(s8 *)(*(u8 **)(r + 0x10) + 3);
        }
        r = c->Slot(1);
        if (r != 0) {
            S16(0xB46) = *(s8 *)(*(u8 **)(r + 0x10) + 3);
        }
    }
    if (c != 0) {
        f = U32(0xA44);
        b = !(f & 0x2000);
        U32(0xA44) = b ? (f & ~0x1000) : (f | 0x1000);
        b = c->Busy(-1);
        U32(0xA44) = b ? (U32(0xA44) & ~0x2000) : (U32(0xA44) | 0x2000);
    }
    if (S32(0x428) != 0) {
        CharaSnapshotMotionMaybe_236c50(p);
        w = ActCfgTableFindAbltByName_222870(S32(0x428), p + 0xAAC);
        if (w != 0) {
            t = ((short)ActInfoAbltGetKind_22ec20(w));
            S16(0xA2C) = t;
            if (t != old) {
                switch (S16(0xA2E)) {
                case 0:
                    if (S32(0x428) != 0) {
                        switch (t) {
                        case 1:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C758);
                            break;
                        default:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C768);
                            break;
                        }
                    }
                    break;
                case 2:
                    if (S32(0x428) != 0) {
                        switch (t) {
                        case 1:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C798);
                            break;
                        default:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C7A8);
                            break;
                        }
                    }
                    break;
                case 3:
                    if (S32(0x428) != 0) {
                        switch (t) {
                        case 1:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C7B8);
                            break;
                        default:
                            ActCfgTableRunEvntByName_21f680(S32(0x428), S16(0x424), D_0045C7C8);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    U32(0xA44) &= ~0x20;
    U32(0xA44) &= ~0x8000;
    if (TargetRefResolve_2e5ed0(p + 0x97C, 0) != 0) {
        U32(0xA44) |= 0x8000;
        if (U32(0xA44) & 0x1000000) {
            if (((short)TargetRefGetKind_2e7130(p + 0x97C)) == 2 || ((short)TargetRefGetKind_2e7130(p + 0x97C)) == 4 || ((short)TargetRefGetKind_2e7130(p + 0x97C)) == 5) {
                if ((((short)TargetRefGetId_2e7120(p + 0x97C)) >= 0 && ((short)TargetRefGetId_2e7120(p + 0x97C)) < 12) ||
                    (((short)TargetRefGetId_2e7120(p + 0x97C)) >= 0x80 && ((short)TargetRefGetId_2e7120(p + 0x97C)) < 0x9C)) {
                    gm = GetGameData_1fede0();
                    o = ActorFindById_3eb870(gm, ((short)TargetRefGetId_2e7120(p + 0x97C)));
                    if (o != 0 && o->Check() != 0) {
                        U32(0xA44) &= ~0x8000;
                    }
                }
            }
        }
    }
    *(u64 *)(p + 0x3D0) = (S16(0xB60) >= 0 && S32(0xB5C) != 0) ? (*(u64 *)(p + 0x3D0) | 0x0100000000000000ULL) : (*(u64 *)(p + 0x3D0) & ~0x0100000000000000ULL);
    if (U32(0xA44) & 0x8000) {
        TargetRefGetPos_2e6a60(p + 0x97C, &v);
        fz = v.z;
        fy = v.y;
        fx = v.x;
        F32(0x470) = fx;
        F32(0x474) = fy;
        F32(0x478) = fz;
        F32(0x47C) = 1.0f;
    }
    CharaGetPos_2388a0(p, &pos);
    S32(0xA4C) = -1;
    unit = GetMapMgr_201a90();
    e = MapFindBlockAtPos_1e3a00(unit, &pos, 0.0f);
    if (e == 0) {
        e = MapGetActiveArea_1e56e0(unit);
        if (e == 0 || ((unsigned char)MapDataIsLoaded_1e79d0(e)) == 0) {
            *(u64 *)(p + 0x3D0) |= 0x0000002000000000ULL;
            U32(0xA44) |= 0x20000;
            S32(0xA4C) = -1;
            return;
        }
        S32(0xA4C) = ((short)MapDataGetId_1e7bd0(e));
        if (*(u32 *)(e + 0x2C) & 0x400) {
            return;
        }
        *(u64 *)(p + 0x3D0) |= 0x0000002000000000ULL;
        U32(0xA44) |= 0x20000;
        return;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(e)) == 0) {
        *(u64 *)(p + 0x3D0) |= 0x0000002000000000ULL;
        U32(0xA44) |= 0x20000;
    }
    S32(0xA4C) = ((short)MapDataGetId_1e7bd0(e));
}
