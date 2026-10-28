/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Info {
    u8 pad0[4];
    s8 sub : 4;
    s8 kind : 4;
} Info;

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isBusy() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * getInfo() { return VCM0(Info *, 0x354); }
};

typedef struct World {
    u8 pad[0x1C];
    s32 x1C;
} World;

extern "C" {
extern s32 GetCurrentScene_1f5be0(void);
extern s32 DListGetHead_42ea60(void *list);
extern s32 DListGetNext_42eb30(s32 node);
extern s32 CharaGetId_214a80(s32 e);
extern s32 CharaGetActionMode_213850(s32 e);
extern u32 ObjRecGetFlags_1c3d90(s32 a, s32 b, s32 c);
extern World *GetGameData_1fede0(void);
extern f32 Sinf_128fd0(f32 a);
extern f32 Cosf_128d30(f32 a);
extern Unit *ObjFindById_3bb3a0(s32 a, s32 b);
extern void CharaGetPos_2388a0(s32 e, Vec *v);
extern void VecSub_1cbd00(Vec *d, Vec *a, Vec *b);
extern f32 VecLengthSqXZ_1cb450(Vec *, void *);
extern f32 CharaGetCollRadius_2386a0(s32 e);
extern void VecNormalize_1cbb80(Vec *d, Vec *s);
extern f32 VecDot3_1cba90(Vec *a, Vec *b);
extern f32 D_0045B080[0x100];
}

extern "C" s32 ActionMgrFindLiftableInFrontMaybe_232de0(u8 *self, Vec *at, f32 ang, f32 rad)
{
    Vec dir __attribute__((aligned(16)));
    Vec pos __attribute__((aligned(16)));
    Vec d __attribute__((aligned(16)));
    s32 ctx;
    s32 node;
    s32 e;
    World *w;
    s32 best;
    f32 lo;
    f32 hi;
    f32 dist;
    Unit *u;
    Info *info;

    ctx = GetCurrentScene_1f5be0();
    node = DListGetHead_42ea60(self + 0x20);
    while (node != 0) {
        e = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (((short)CharaGetId_214a80(e)) < 0x80) {
            continue;
        }
        if (!(((short)CharaGetId_214a80(e)) < 0x9C)) {
            continue;
        }
        if (((short)CharaGetActionMode_213850(e)) == 0x12) {
            return -1;
        }
        if (!(ObjRecGetFlags_1c3d90(ctx, 1, ((short)CharaGetId_214a80(e))) & 0x800000)) {
            return -1;
        }
    }
    w = GetGameData_1fede0();
    {
        u8 *p = (u8 *)&dir;
        u32 n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
    }
    dir.x = Sinf_128fd0(ang);
    dir.z = Cosf_128d30(ang);
    hi = D_0045B080[0];
    lo = -0.5f * hi;
    best = -1;
    node = DListGetHead_42ea60(self + 0x20);
    while (node != 0) {
        e = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (((short)CharaGetId_214a80(e)) < 0x80) {
            continue;
        }
        if (!(((short)CharaGetId_214a80(e)) < 0x9C)) {
            continue;
        }
        if (((short)CharaGetActionMode_213850(e)) == 0x12) {
            continue;
        }
        u = ObjFindById_3bb3a0(w->x1C, ((short)CharaGetId_214a80(e)));
        if (u == 0) {
            continue;
        }
        if (u->isBusy() != 0) {
            continue;
        }
        info = u->getInfo();
        if (info == 0) {
            continue;
        }
        if (info->kind == 0) {
            continue;
        }
        CharaGetPos_2388a0(e, &pos);
        VecSub_1cbd00(&d, &pos, at);
        if (d.y < lo) {
            continue;
        }
        if (!(d.y <= hi)) {
            continue;
        }
        dist = VecLengthSqXZ_1cb450(&d, 0);
        if (!(dist <= (rad + CharaGetCollRadius_2386a0(e)) * (rad + CharaGetCollRadius_2386a0(e)))) {
            continue;
        }
        d.y = 0.0f;
        VecNormalize_1cbb80(&d, &d);
        if (VecDot3_1cba90(&d, &dir) < 0.5f) {
            continue;
        }
        if (ObjFindById_3bb3a0(w->x1C, ((short)CharaGetId_214a80(e))) == 0) {
            continue;
        }
        best = ((short)CharaGetId_214a80(e));
    }
    return best;
}
