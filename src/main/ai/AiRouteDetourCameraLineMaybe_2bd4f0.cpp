#pragma opt_repositioncode on
#include "types.h"

struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

class VC {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void getPos(Vec *out);
};

struct World {
    u8 pad0[0x4344];
    s32 x4344;
};

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
VC *ObjRecGetLiveObject_1c3bc0(World *, s32);
World *GetStaticScene_1c6c70();
f32 SegmentProjectTXZ_1ca2a0(Vec *, Vec *, Vec *);
f32 VecDistSqXZ_1cb390(Vec *, Vec *);
void VecNormalizeXZ_1cbb50(Vec *, Vec *);
void VecScale_1cbca0(Vec *, Vec *, f32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
void VecCopy_1cbe30(Vec *, Vec *);
s32 GetActionMgr_1fdb50();
s32 CharaGetId_214a80(s32);
s32 ActionMgrGetCharaList_233b40(s32);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, Vec *);
f32 AiGetApproachMarginMaybe_2c0fc0(s32);
s32 AiGetTargetCharaId_2c0fd0(s32);
s32 DListGetHead_42ea60(s32);
s32 DListGetNext_42eb30(s32);
extern f32 D_0047DB6C;
extern f32 D_0047DB70;
}

extern "C" void AiRouteDetourCameraLineMaybe_2bd4f0(s32 arg0, s32 *arg1, Vec *arg2, Vec *arg3, f32 radius) {
    Vec pos;
    Vec dir;
    Vec cam;
    Vec opos;
    Vec a;
    Vec b;
    Vec d;
    Vec r1;
    Vec r2;
    s32 self;
    s32 grp;
    VC *vc;
    World *w;
    f32 t;
    f32 lim;
    s32 n;
    s32 o;
    s32 id;
    bool le;
    s32 side;
    f32 c;
    f32 s;

    if (arg1 == 0) {
        return;
    }
    self = *arg1;
    if (self == 0) {
        return;
    }
    CharaGetPos_2388a0(self, &pos);
    grp = GetActionMgr_1fdb50();
    if (ActionMgrFindById_233b50(grp, AiGetTargetCharaId_2c0fd0(arg0)) == 0) {
        return;
    }
    VecCopy_1cbe30(&dir, arg2);
    w = GetStaticScene_1c6c70();
    vc = ObjRecGetLiveObject_1c3bc0(w, w->x4344);
    if (vc == 0) {
        return;
    }
    vc->getPos(&cam);
    t = dir.y;
    cam.y = t;
    t = SegmentProjectTXZ_1ca2a0(&pos, &dir, &cam);
    if (t <= 0.0f) {
        return;
    }
    if (1.0f <= t) {
        return;
    }
    lim = D_0047DB6C * radius;
    lim = lim * lim;
    for (n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(grp)); n != 0; ) {
        o = n + 0x10;
        n = DListGetNext_42eb30(n);
        id = CharaGetId_214a80(o);
        if (id == CharaGetId_214a80(self)) {
            continue;
        }
        id = CharaGetId_214a80(o);
        if (id == AiGetTargetCharaId_2c0fd0(arg0)) {
            continue;
        }
        CharaGetPos_2388a0(o, &opos);
        if (VecDistSqXZ_1cb390(&pos, &opos) < lim) {
            return;
        }
    }
    VecSub_1cbd00(&b, &dir, &cam);
    VecSub_1cbd00(&a, &pos, &cam);
    le = b.z * a.x - b.x * a.z <= 0.0f;
    side = (u8)!le;
    VecSub_1cbd00(&d, &dir, &cam);
    VecNormalizeXZ_1cbb50(&d, &d);
    VecScale_1cbca0(&d, &d, AiGetApproachMarginMaybe_2c0fc0(arg0));
    c = Cosf_128d30(D_0047DB70);
    s = Sinf_128fd0(D_0047DB70);
    if (side < 1) {
        VecCopy_1cbe30(&r1, &d);
        d.x = r1.x * c + -s * r1.z;
        d.z = r1.x * s + c * r1.z;
    } else {
        VecCopy_1cbe30(&r2, &d);
        d.x = r2.x * c + s * r2.z;
        d.z = r2.x * -s + c * r2.z;
    }
    VecAdd_1cbdc0(&dir, &dir, &d);
    VecSub_1cbd00(arg3, &dir, &pos);
    VecNormalizeXZ_1cbb50(arg3, arg3);
}
