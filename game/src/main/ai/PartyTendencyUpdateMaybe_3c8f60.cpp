/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Unit3c8 {
    u8 pad0[0xA0];
    V4 mA0[8];
    u8 pad120[0x128 - 0x120];
    f32 m128;
    f32 m12C;
    f32 m130;
    f32 m134;
    f32 m138;
    s16 m13C;
    u8 pad13E[2];
    f32 m140;
    u8 pad144[0x150 - 0x144];
    V4 m150;
    u8 pad160[0x18C - 0x160];
    s16 m18C;
    s16 m18E;
    s16 m190[8];
} Unit3c8;

typedef struct Game3c8 {
    u8 pad0[0x14];
    s32 m14;
    Unit3c8 *m18;
} Game3c8;

class Act3c8 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v6C(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
};

typedef struct Ai3c8 {
    u8 pad0[0xC];
    s32 mC;
} Ai3c8;

typedef struct Ctx3c8 {
    u8 pad0[0x30];
} Ctx3c8;

extern "C" {
f32 RandFloat_13c010(void);
f32 VecDistance_13d3d0(V4 *, V4 *);
void VecCopy_1cbe30(V4 *, V4 *);
f32 GameSceneGetTimeStep_1ceba0(s32);
s32 GetCurrentScene_1f5be0(void);
s32 CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountMembers_3c2010(Unit3c8 *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Unit3c8 *, s32);
s32 SkillGetCharaStateMaybe_3e0df0(s32);
u8 SkillTriggerEvalMaybe_3e1200(Ctx3c8 *, Act3c8 *);
void ActionPacketInitTendencyMaybe_3e2c00(Ctx3c8 *, s32, s32, s32, f32);
void ActionPacketReset_3e3d00(Ctx3c8 *);
extern f32 D_00465938[];
extern f32 D_00465940[];
extern f32 D_00465948[];
extern f32 D_00465950[];
extern f32 D_00465958[];
extern f32 D_00465960[];
extern f32 D_00465968[];
extern f32 D_00465970[];
extern f32 D_00465978[];
extern f32 D_00465980[];
extern f32 D_00465988[];
extern f32 D_00465990[];
extern f32 D_00465998[];
extern f32 D_004659A0[];
extern Game3c8 *D_00483890;
extern u8 D_004839A0;
s32 PartyTendencyUpdateMaybe_3c8f60(Unit3c8 *arg0, u32 arg1);
}

static inline s32 FindIdx(Unit3c8 *u)
{
    s32 i;
    s32 n = u->m18C;
    for (i = 0; i < n; i++) {
        if (u->m190[i] == u->m18E) {
            return i;
        }
    }
    return -1;
}

#define CLAMP(f)                                   \
    if (arg0->f < D_00465940[0]) {                 \
        arg0->f = D_00465940[0];                   \
    } else if (!(arg0->f <= D_00465938[0])) {      \
        arg0->f = D_00465938[0];                   \
    }

s32 PartyTendencyUpdateMaybe_3c8f60(Unit3c8 *arg0, u32 arg1)
{
    Ai3c8 *list[4];
    Act3c8 *out[4];
    Ctx3c8 ctx __attribute__((aligned(16)));
    f32 dt;
    s32 i;
    f32 fw;
    f32 bk;
    f32 x;
    bool ok;
    s32 sys;
    s32 n;
    s32 j;
    s32 k;
    s32 cnt;
    Ai3c8 **pp;
    Ai3c8 *a;
    Act3c8 *o;

    dt = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    i = FindIdx(D_00483890->m18);
    fw = D_00465990[0] * dt;
    bk = D_00465998[0] * dt;
    arg0->m138 = (f32)(s32)arg1;
    arg0->m13C = 0;
    *(s32 *)&arg0->m140 = 0;
    switch (arg1) {
    case 0:
    case 7:
        arg0->m140 = 2.0f;
        arg0->m128 += fw;
        arg0->m12C -= bk;
        arg0->m130 -= bk;
        arg0->m134 -= bk;
        x = arg0->m128;
        if (x >= D_00465948[0]) {
            arg0->m13C = 0xA;
        } else if (x >= D_00465950[0]) {
            arg0->m13C = 6;
        } else if (x >= D_00465988[0]) {
            arg0->m13C = 2;
            arg0->m12C = D_00465940[0];
            arg0->m130 = D_00465940[0];
            arg0->m134 = D_00465940[0];
            VecCopy_1cbe30(&arg0->m150, &arg0->mA0[i]);
        }
        break;
    case 2:
    case 4:
        arg0->m140 = 1.0f;
        arg0->m128 -= bk;
        arg0->m12C += fw;
        arg0->m130 -= bk;
        arg0->m134 -= bk;
        x = arg0->m12C;
        if (x >= D_00465958[0]) {
            arg0->m13C = 9;
        } else if (x >= D_00465960[0]) {
            arg0->m13C = 5;
        } else if (x >= D_00465988[0]) {
            x = D_00465940[0];
            arg0->m13C = 1;
            arg0->m128 = x;
            arg0->m130 = x;
            arg0->m134 = x;
        }
        break;
    case 3:
        arg0->m140 = 3.0f;
        arg0->m128 -= bk;
        arg0->m12C -= bk;
        arg0->m130 += fw;
        arg0->m134 -= bk;
        x = arg0->m130;
        if (x >= D_00465968[0]) {
            arg0->m13C = 0xB;
        } else if (x >= D_00465970[0]) {
            arg0->m13C = 7;
        } else if (x >= D_00465988[0]) {
            x = D_00465940[0];
            arg0->m13C = 3;
            arg0->m128 = x;
            arg0->m12C = x;
            arg0->m134 = x;
        }
        break;
    case 5:
        arg0->m140 = 4.0f;
        arg0->m128 -= bk;
        arg0->m12C -= bk;
        arg0->m130 -= bk;
        x = arg0->m134 + fw;
        arg0->m134 = x;
        if (x >= D_00465978[0]) {
            arg0->m13C = 0xC;
        } else if (x >= D_00465980[0]) {
            arg0->m13C = 8;
        } else if (x >= D_00465988[0]) {
            x = D_00465940[0];
            arg0->m13C = 4;
            arg0->m128 = x;
            arg0->m12C = x;
            arg0->m130 = x;
        }
        break;
    case 1:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    default:
        arg0->m128 -= bk;
        arg0->m12C -= bk;
        arg0->m130 -= bk;
        arg0->m134 -= bk;
        break;
    }
    CLAMP(m128)
    CLAMP(m12C)
    CLAMP(m130)
    CLAMP(m134)
    if (D_004839A0 == 0) {
        return 1;
    }
    ok = false;
    switch (arg0->m13C) {
    case 0:
        ok = false;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        ok = false;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        ok = true;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        ok = true;
        break;
    }
    if (!ok) {
        return 0;
    }
    if (D_00483890 == 0) {
        return 0;
    }
    if (D_004659A0[0] * RandFloat_13c010() <= 1.0f) {
        sys = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&ctx);
        i = FindIdx(arg0);
        ActionPacketInitTendencyMaybe_3e2c00(&ctx, sys, arg0->m13C, 0, VecDistance_13d3d0(&arg0->mA0[i], &arg0->m150));
        n = PartyCountMembers_3c2010(arg0, 1, 1);
        list[0] = D_00483890 == 0 ? 0 : (Ai3c8 *)CharaMgrPoolFindById_3a8c60(D_00483890->m14, arg0->m18E);
        for (j = 1; j < n; j++) {
            if (D_00483890 == 0) {
                a = 0;
            } else {
                k = ((short)PartyGetNonLeaderId_3c2750(arg0, j - 1));
                if (k < 0) {
                    a = 0;
                } else {
                    a = (Ai3c8 *)CharaMgrPoolFindById_3a8c60(D_00483890->m14, k);
                }
            }
            list[j] = a;
        }
        cnt = 0;
        for (j = 0; j < n; j++) {
            pp = &list[j];
            a = *pp;
            if (a != 0) {
                switch (SkillGetCharaStateMaybe_3e0df0(a->mC)) {
                case 0:
                    out[cnt++] = (Act3c8 *)a;
                case 1:
                case 3:
                    *pp = 0;
                    break;
                case 2:
                    break;
                }
            }
        }
        for (k = 0; k < n; k++) {
            a = list[k];
            if (a != 0) {
                list[k] = 0;
                out[cnt++] = (Act3c8 *)a;
            }
        }
        for (j = 0; j < cnt; j++) {
            o = out[j];
            if (o != 0 && o->v6C(0) != 0 && (SkillTriggerEvalMaybe_3e1200(&ctx, o) & 0xFF) != 0) {
                break;
            }
        }
    }
    return 1;
}
