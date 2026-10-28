/* rgp:protos */
#line 1
#include "types.h"
#pragma inline_depth(8)

typedef struct Pos {
    u8 pad0[0x1F0];
    s32 v[3];
} Pos;

typedef struct Actor {
    u8 pad0[0x3D0];
    u64 x3D0;
    u32 x3D8;
    u8 pad3DC[0x3F4 - 0x3DC];
    Pos *x3F4;
    u8 pad3F8[0x424 - 0x3F8];
    s16 x424;
    u8 pad426[0xA2C - 0x426];
    s16 xA2C;
    s16 xA2E;
    s16 xA30;
    s16 xA32;
    s16 xA34;
    s16 xA36;
    s16 xA38;
    u8 padA3A[0xA44 - 0xA3A];
    u32 xA44;
} Actor;

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v168() { return VCM0(s32, 0x2A8); }
};

typedef struct Sub44 {
    u8 pad0[0x44];
    s16 x44;
} Sub44;

extern "C" char D_0045C830[];
extern "C" char D_0045C840[];
extern "C" char D_0045C848[];
extern "C" char D_0045C858[];
extern "C" char D_0045C868[];
extern "C" char D_0045C870[];
extern "C" f32 D_0045B080[];
extern "C" s64 D_0047D1A8;
extern "C" f32 D_0047DB20;

extern "C" s32 IsInBattle_288420(void);
extern "C" void CharaSetActionModeAppear_21c920(Actor *);
extern "C" void *GetGameData_1fede0(void);
extern "C" void *ActorFindById_3eb870(void *, s32);
extern "C" void CharaEnterDeathStateMaybe_217a00(Actor *);
extern "C" void CharaSetActionModeDeath_217d70(Actor *);
extern "C" char *strcpy(char *, const char *);
extern "C" s32 Sprintf_1343b8(char *, const char *, ...);
extern "C" s32 MotionListFindByName_1721d0(s32 *, char *, s32 *, s32 *);
extern "C" void CharaSetActionModeDamage_2190c0(Actor *);
extern "C" void CharaSetActionModeBlownAway_218840(Actor *);
extern "C" void *CharaGetHangLedge_238260(Actor *);
extern "C" s32 CharaHangLedgeIsValid_23a280(void *);
extern "C" s32 CharaIsHeadUnderwaterMaybe_238250(Actor *);
extern "C" f32 CharaGetHeadHeightMaybe_238360(Actor *);
extern "C" f32 CharaGetWaterDepthMaybe_238370(Actor *);
extern "C" f32 CharaGetHeightAboveGround_238380(Actor *);
extern "C" double fptodp(f32);
extern "C" double dpmul(double, double);
extern "C" double dpsub(double, double);
extern "C" s32 DoubleGreaterEqual_100230(double, double);
extern "C" void CharaSetActionModeSwim_21b170(Actor *);
extern "C" s32 CharaSwimShouldContinueMaybe_20f8f0(Actor *);
extern "C" void CharaResetToBaseMode_21e830(Actor *);
extern "C" Sub44 *CharaGetGroundTri_238410(Actor *, s32);
extern "C" void CharaSetActionModeMoveMotion_21bbb0(Actor *);

static inline bool NoBit58(Actor *p)
{
    return !(p->x3D0 & ((u64)0x04000000 << 32));
}

static inline bool NoBit59(Actor *p)
{
    return !(p->x3D0 & ((u64)0x08000000 << 32));
}

static inline s32 Lookup(Actor *p, char *buf)
{
    Pos *q = p->x3F4;
    s32 v[3];
    s32 a, b;
    switch ((u32)q) {
    case 0:
        return 0;
    default:
        v[0] = q->v[0];
        v[1] = q->v[1];
        v[2] = q->v[2];
        return MotionListFindByName_1721d0(v, buf, &a, &b);
    }
}

static inline bool IsSpecial(Actor *p, char *buf)
{
    if (buf[0] == '#') return 1;
    return Lookup(p, buf) != 0;
}

static inline bool Check6(Actor *p)
{
    void *q;
    if (!NoBit58(p)) return 0;
    q = CharaGetHangLedge_238260(p);
    if (q == 0 || CharaHangLedgeIsValid_23a280(q) == 0) return 0;
    return 1;
}

static inline bool CheckY(Actor *p)
{
    u32 f;
    f32 k, a;
    if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(p))) return 1;
    f = p->x3D8;
    if (!(f & 0x10)) return 0;
    if (!(f & 4)) return 1;
    k = D_0047DB20 * (f32)D_0045B080[0];
    a = CharaGetWaterDepthMaybe_238370(p);
    a = a + k;
    if (a < CharaGetHeadHeightMaybe_238360(p)) return 0;
    if (!(CharaGetHeightAboveGround_238380(p) <= k)) return 1;
    return 0;
}

static inline bool ShouldAct(Actor *p)
{
    if (!NoBit59(p)) return 0;
    switch (p->xA32) {
    case 4:
        switch (p->xA34) {
        case 0:
            return 0;
        case 1:
        case 2: {
        s64 d;
        if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(p))) return 1;
        if (p->x3D8 & 0x10) {
            s64 a = ((s64)__builtin_bit_cast(long long, fptodp(CharaGetHeadHeightMaybe_238360(p))));
            s64 k = D_0047D1A8;
            d = ((s64)__builtin_bit_cast(long long, dpsub(__builtin_bit_cast(double, (long long)(a)), dpmul(__builtin_bit_cast(double, (long long)(k)), fptodp(D_0045B080[0])))));
            if (((unsigned char)DoubleGreaterEqual_100230(fptodp(CharaGetWaterDepthMaybe_238370(p)), __builtin_bit_cast(double, (long long)(d))))) return 1;
        }
        return 0;
        }
        }
        return 0;
    case 5:
        return 0;
    }
    return CheckY(p);
}

extern "C" s16 CharaSelectStateFromFlagsMaybe_20e9f0(Actor *p, s64 flags)
{
    switch (p->xA32) {
    case 17:
        p->xA38 = 0;
        return p->xA32;
    case 10:
    case 18:
        return p->xA32;
    default:
        if (!(p->xA44 & 0x40000000)) {
            if ((p->x424 >= 0 && p->x424 < 12) || ((unsigned char)IsInBattle_288420())) {
                CharaSetActionModeAppear_21c920(p);
                return p->xA32;
            }
        }
        if (!(p->xA44 & 0x200000) && (flags & ((s64)0x800 << 32))) {
            VObj *o = (VObj *)ActorFindById_3eb870(GetGameData_1fede0(), p->x424);
            if (o != 0 && o->v168()) {
                CharaEnterDeathStateMaybe_217a00(p);
                return p->xA32;
            }
            CharaSetActionModeDeath_217d70(p);
            return p->xA32;
        }
        if (p->xA36 != 0x15 && p->xA36 != 0x16 && p->xA36 != 0x17 && p->xA32 != 0x10) {
            if (flags & ((s64)8 << 32)) {
                char buf[0x28] __attribute__((aligned(16)));
                if (p->xA2E == 2) {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C830);
                    } else {
                        Sprintf_1343b8(buf, D_0045C840, p->xA2C + 0x60, D_0045C848);
                    }
                } else if (p->xA2E == 3) {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C858);
                    } else {
                        Sprintf_1343b8(buf, D_0045C868, p->xA2C + 0x60, D_0045C848);
                    }
                } else {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C848);
                    } else {
                        Sprintf_1343b8(buf, D_0045C870, p->xA2C + 0x60, D_0045C848);
                    }
                    strcpy(buf, D_0045C848);
                }
                if (!IsSpecial(p, buf)) {
                    CharaSetActionModeDamage_2190c0(p);
                    return p->xA32;
                }
                CharaSetActionModeBlownAway_218840(p);
                return p->xA32;
            }
            if (flags & ((s64)4 << 32)) {
                CharaSetActionModeDamage_2190c0(p);
                return p->xA32;
            }
        }
        if (p->xA38 == 0) {
            s16 st = p->xA32;
            switch (st) {
            case 7:
                return p->xA32;
            case 6:
                if (Check6(p)) return p->xA32;
                break;
            case 0xF:
            case 0x10:
                return p->xA32;
            }
        }
        if (ShouldAct(p)) {
            CharaSetActionModeSwim_21b170(p);
            return p->xA32;
        }
        if (p->xA38 == 0) {
            switch (p->xA32) {
            case 5:
                if (!CharaSwimShouldContinueMaybe_20f8f0(p)) {
                    CharaResetToBaseMode_21e830(p);
                    return p->xA32;
                }
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                if ((p->x3D8 & 4) && CharaGetGroundTri_238410(p, 0)->x44 == 8) {
                    CharaSetActionModeMoveMotion_21bbb0(p);
                    p->xA34 = 0x65;
                    return p->xA32;
                }
                break;
            case 6:
            case 7:
                CharaResetToBaseMode_21e830(p);
                break;
            case 4:
            case 10:
            case 15:
            case 16:
            case 17:
                break;
            default:
                p->xA2E = 0;
                CharaResetToBaseMode_21e830(p);
                break;
            }
        }
        return p->xA32;
    }
    return p->xA32;
}
