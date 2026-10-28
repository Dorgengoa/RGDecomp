/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

struct V2330f0 {
    f32 x, y, z, w;
};

class C2330f0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vB0() { return VCM0(s32, 0xB0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v19C(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
};

struct R2330f0 {
    u8 pad0[0x1C];
    s32 w1C;
};

struct P2330f0 {
    u8 pad0[4];
    s16 h4;
};

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 VecLengthSqXZ_1cb450(V2330f0 *, void *);
f32 VecDot3_1cba90(V2330f0 *, V2330f0 *);
void VecNormalize_1cbb80(V2330f0 *, V2330f0 *);
void VecSub_1cbd00(V2330f0 *, V2330f0 *, s32);
R2330f0 *GetGameData_1fede0(void);
s32 CharaIsTargetableMaybe_210280(u8 *);
s32 CharaHasEvObjContact_214960(u8 *);
P2330f0 *CharaGetEvObjContact_214990(u8 *);
s32 CharaGetId_214a80(u8 *);
f32 CharaGetCollRadius_2386a0(u8 *);
void CharaGetPos_2388a0(u8 *, V2330f0 *);
s32 TargetRefResolve_2e5ed0(s32, s32);
void TargetRefSetModel_2e66c0(s32, s32, f32);
C2330f0 *ObjFindById_3bb3a0(s32, s32);
u8 *DListGetHead_42ea60(u8 *);
u8 *DListGetNext_42eb30(u8 *);
}
extern "C" f32 D_0045B080[4];

extern "C" s32 ActionMgrFindTargetInFrontMaybe_2330f0(u8 *obj, s32 arg1, s32 arg2, f32 ang, f32 rad)
{
    R2330f0 *r;
    V2330f0 tmp __attribute__((aligned(16)));
    V2330f0 b0 __attribute__((aligned(16)));
    V2330f0 a0 __attribute__((aligned(16)));
    f32 lo;
    f32 lim;
    s32 ret;
    u8 *node;
    u8 *e;
    C2330f0 *o;
    f32 d;
    f32 rr;
    u8 *p;
    u32 n;

    if (arg1 == 0) {
        return -1;
    }
    r = GetGameData_1fede0();
    p = (u8 *)&tmp;
    n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    tmp.x = Sinf_128fd0(ang);
    tmp.z = Cosf_128d30(ang);
    lim = D_0045B080[0];
    lo = -0.5f * lim;
    ret = -1;
    node = DListGetHead_42ea60(obj + 0x20);
    while (node != 0) {
        e = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (((short)CharaGetId_214a80(e)) < 0x80) {
            continue;
        }
        if (((short)CharaGetId_214a80(e)) >= 0x9C) {
            continue;
        }
        if (CharaIsTargetableMaybe_210280(e) == 0) {
            continue;
        }
        CharaGetPos_2388a0(e, &b0);
        VecSub_1cbd00(&a0, &b0, arg2);
        if (a0.y < lo) {
            continue;
        }
        if (!(a0.y <= lim)) {
            continue;
        }
        d = VecLengthSqXZ_1cb450(&a0, 0);
        if (!(d <= (rad + CharaGetCollRadius_2386a0(e)) * (rad + CharaGetCollRadius_2386a0(e)))) {
            continue;
        }
        a0.y = 0.0f;
        VecNormalize_1cbb80(&a0, &a0);
        if (VecDot3_1cba90(&a0, &tmp) < 0.5f) {
            continue;
        }
        o = ObjFindById_3bb3a0(r->w1C, ((short)CharaGetId_214a80(e)));
        if (o == 0) {
            continue;
        }
        {
            bool b = o->vB0() && !o->v19C(0x1F);
            ret = b;
        }
        if (CharaHasEvObjContact_214960(e) != 0 && CharaGetEvObjContact_214990(e)->h4 == 3) {
            ret = 0;
        }
        TargetRefSetModel_2e66c0(arg1, ((short)CharaGetId_214a80(e)), CharaGetCollRadius_2386a0(e));
    }
    if (TargetRefResolve_2e5ed0(arg1, 0) == 0) {
        ret = -1;
    }
    return ret;
}
