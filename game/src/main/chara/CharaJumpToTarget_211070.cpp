/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Obj {
    u8 pad[0x3D0];
    u64 flags;
} Obj;

typedef struct Self {
    u8 pad000[0x3D8];
    s32 w3D8;
    u8 pad3DC[0x428 - 0x3DC];
    s32 w428;
    u8 pad42C[0x930 - 0x42C];
    u8 x930[0x97C - 0x930];
    u8 x97C[0xA2E - 0x97C];
    s16 hA2E;
    u8 padA30[6];
    s16 hA36;
    u8 padA38[0xA44 - 0xA38];
    s32 wA44;
} Self;

extern "C" {
f32 VecLength_1cb4c0(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
s32 GetActionMgr_1fdb50(void);
void CharaMoveReqSet_219310(void *, Vec *, s32, s32);
f32 ActCfgTableGetJumpHeightMaybe_223cc0(s32);
Obj *ActionMgrFindById_233b50(s32, s32);
f32 CharaGetGroundY_238350(Self *);
void CharaGetPos_2388a0(Self *, Vec *);
void TargetRefGetPos_2e6a60(void *, Vec *);
s32 TargetRefIsActive_2e6f00(void *);
f32 TargetRefGetRadius_2e7100(void *);
s32 TargetRefGetId_2e7120(void *);
s32 TargetRefGetKind_2e7130(void *);
extern f32 D_0045B080[4];
}

extern "C" s32 CharaJumpToTarget_211070(Self *self, s32 arg1, f32 off, f32 lim) {
    Vec pos __attribute__((aligned(16)));
    Vec tgt __attribute__((aligned(16)));
    Vec dir __attribute__((aligned(16)));
    bool ok;
    void *p;
    s32 t;
    s32 h;
    Obj *q;
    f32 unit;
    f32 base;
    f32 d;
    f32 lo;
    f32 hi;
    f32 ymax;
    f32 y;
    f32 len;
    f32 x;
    f32 nl;

    ok = true;
    if (self->hA2E != 2 && self->hA2E != 3) {
        ok = false;
    }
    if (!ok) {
        return 0;
    }
    if (!(self->wA44 & 0x8000)) {
        return 0;
    }
    p = self->x97C;
    if (TargetRefIsActive_2e6f00(p) == 0) {
        return 0;
    }
    t = ((short)TargetRefGetKind_2e7130(p));
    if (t != 5 && t != 4) {
        return 0;
    }
    h = GetActionMgr_1fdb50();
    q = ActionMgrFindById_233b50(h, ((short)TargetRefGetId_2e7120(p)));
    if (q != 0 && !(q->flags & 0x8000000000000ULL)) {
        return 0;
    }
    CharaGetPos_2388a0(self, &pos);
    TargetRefGetPos_2e6a60(p, &tgt);
    unit = D_0045B080[0];
    tgt.y -= 0.75f * unit;
    if (self->w3D8 & 4) {
        base = CharaGetGroundY_238350(self);
        d = tgt.y - base;
        hi = 3.0f * D_0045B080[0];
        lo = 2.0f * D_0045B080[0];
        if (d < lo) {
            d = lo;
        }
        if (!(d <= hi)) {
            d = hi;
        }
        tgt.y = base + d;
    }
    VecSub_1cbd00(&dir, &tgt, &pos);
    ymax = 5.0f * unit;
    if (self->hA36 == 2) {
        dir.y -= ActCfgTableGetJumpHeightMaybe_223cc0(self->w428);
        ymax -= ActCfgTableGetJumpHeightMaybe_223cc0(self->w428);
    }
    y = dir.y;
    dir.y = 0.0f;
    len = VecLength_1cb4c0(&dir);
    x = (len - TargetRefGetRadius_2e7100(p)) - off;
    nl = -lim;
    if (x < nl) {
        x = nl;
    }
    if (!(x <= lim)) {
        x = lim;
    }
    VecScaleToLength_1cb510(&dir, &dir, x);
    if (!(y <= ymax)) {
        y = ymax;
    }
    dir.y = y;
    CharaMoveReqSet_219310(self->x930, &dir, arg1, 2);
    return 1;
}
