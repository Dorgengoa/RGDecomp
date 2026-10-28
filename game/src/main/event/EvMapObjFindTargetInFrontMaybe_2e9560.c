/* rgp:protos */
#define RGP_SELF_EvMapObjFindTargetInFrontMaybe_2e9560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Elem {
    u8 pad0[0x32];
    s16 x32;
    u8 pad34[0x6C - 0x34];
    u8 x6C[4];
} Elem;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];


s32 EvMapObjFindTargetInFrontMaybe_2e9560(s32 arg0, s32 arg1, s32 arg2, f32 ang, f32 rad) {
    Vec dir __attribute__((aligned(16)));
    Elem *buf[0x140];
    Vec v100 __attribute__((aligned(16)));
    Vec vF0 __attribute__((aligned(16)));
    s32 ctx;
    f32 lo;
    f32 hi;
    u8 *it;
    s32 s3v;
    s32 s2v;
    s32 n;
    Elem **pp;
    s32 i;
    f32 len;
    u8 *p;
    u128 a;
    u128 b;

    if (arg1 == 0) {
        return 0;
    }
    ctx = ((s32)GetMapMgr_201a90());
    {
        u8 *q = (u8 *)&dir;
        u32 k = 16;
        if (q != 0) {
            do {
                *q = 0;
                k--;
                q++;
            } while (k != 0);
        }
    }

    dir.x = Sinf_128fd0(ang);
    dir.z = Cosf_128d30(ang);
    hi = D_0045B080[0];
    lo = -0.5f * hi;
    for (it = ((u8 *)DListGetHead_42ea60(((s32)EventObjMgrGetTypeList_2e9d60(arg0, 8)))); it != 0; it = ((u8 *)DListGetNext_42eb30(it))) {
        s3v = ((s32)EvObjGetTargetRef_2f9ca0(it + 0x10));
        s2v = MapSlotsFindById_1e4b90(ctx, ((short)TargetRefGetId_2e7120(s3v)), 0);
        if (s2v == 0) {
            continue;
        }
        n = MapDataFindObjsByName_1e6d40(s2v, EvMapObjGetName_366b90(it + 0x10), buf, 0x140);
        if (n <= 0) {
            continue;
        }
        for (pp = buf, i = 0; i < n; i++, pp++) {
            if ((*pp)->x32 == 0) {
                continue;
            }
            NodeGetWorldPos_186100(*pp, &v100);
            VecSub_1cbd00(&vF0, &v100, arg2);
            if (vF0.y >= lo && vF0.y <= hi) {
                len = VecLengthSqXZ_1cb450(&vF0, 0);
                if (len <= (rad + TargetRefGetRadius_2e7100(s3v)) * (rad + TargetRefGetRadius_2e7100(s3v))) {
                    vF0.y = 0.0f;
                    VecNormalize_1cbb80(&vF0, &vF0);
                    if (!(VecDot3_1cba90(&vF0, &dir) < 0.5f)) {
                        p = (*pp)->x6C;
                        a = MapDataGetId_1e7bd0(s2v);
                        b = EvMapObjGetId_366b70(it + 0x10);
                        TargetRefSetMapObjKind8_2e63f0(arg1, a, p, b, EvMapObjGetRadiusMaybe_366b60(it + 0x10));
                    }
                }
            }
        }
    }
    return TargetRefResolve_2e5ed0(arg1, 0);
}
