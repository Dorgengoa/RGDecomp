#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct {
    f32 m[4][4];
} Mtx;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 WrapAngle_13c050(f32);
extern void MtxMulVec4_13c900(Vec4 *, Mtx *, Vec4 *);
extern void MtxRotY_13ce20(Mtx *, f32);
extern void FrameGetWorldPos_148f30(s32, Vec4 *);
extern s32 ModelGetRootFrame_1511a0(u8 *);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void AxisAngleBetweenVecs_1d7da0(Vec4 *, f32 *, Vec4 *, Vec4 *);
extern void VecRotateAxisAngle_1d7f10(Vec4 *, Vec4 *, Vec4 *, f32);
extern void CharaSetYaw_2138f0(s32, f32);
extern void CharaGetPos_2388a0(s32, Vec4 *);
extern void CharaGetRot_2388b0(s32, Vec4 *);
extern void ScriptSlotStoreFloatRef_2cc8e0(s64 *, f32);
extern f32 ScriptSlotGetFloat_2cc9a0(s64 *);
extern s32 ScriptSlotGetInt_2cc9c0(s64 *);
extern f32 D_0047D1DC;
extern s32 D_004DB920[];
extern s32 D_004DB92C[];

s32 AiCmdTurnTowardOffset_2c84d0(s64 *args, s32 arg1) {
    f32 dist;
    Vec4 pos;
    Vec4 rot;
    Vec4 target;
    Vec4 dir;
    Mtx mtx;
    Vec4 v60;
    Vec4 v50;
    s32 n;
    s32 t;
    s32 idx;
    u8 *obj;
    s32 r;
    f32 maxv;
    f32 f;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    CharaGetPos_2388a0(D_004DB92C[0], &pos);
    CharaGetRot_2388b0(D_004DB92C[0], &rot);
    t = *(s32 *)args;
    if (t == 1) {
        target.x = ScriptSlotGetFloat_2cc9a0(args++);
        target.y = 0.0f;
        ScriptSlotGetFloat_2cc9a0(args++);
        target.z = ScriptSlotGetFloat_2cc9a0(args++);
        n = 6;
        target.w = 0.0f;
    } else if (t == 0) {
        idx = ScriptSlotGetInt_2cc9c0(args++);
        if (idx < 0) {
            return 1;
        }
        obj = ObjRecGetLiveObject_1c4a90(D_004DB920[0], idx);
        if (obj == 0) {
            return 0;
        }
        r = ModelGetRootFrame_1511a0(obj);
        if (r != 0) {
            FrameGetWorldPos_148f30(r, &target);
        } else {
            *(u128 *)&target = *(u128 *)(obj + 0x180);
        }
        target.w = 0.0f;
        n = 4;
    }
    dist = ScriptSlotGetFloat_2cc9a0(args++);
    maxv = ScriptSlotGetFloat_2cc9a0(args++);
    if (pos.x == target.x && pos.z == target.z) {
        return 1;
    }
    dir.x = Sinf_128fd0(rot.y);
    dir.y = 0.0f;
    dir.z = Cosf_128d30(rot.y);
    dir.w = 0.0f;
    MtxRotY_13ce20(&mtx, -dist);
    MtxMulVec4_13c900(&dir, &mtx, &dir);
    VecSub_13be40(&v50, &target, &pos);
    v50.y = 0.0f;
    VecNormalize_13bd90(&v50, &v50);
    AxisAngleBetweenVecs_1d7da0(&v60, &dist, &dir, &v50);
    if (dist > maxv) {
        dist = maxv;
    }
    VecRotateAxisAngle_1d7f10(&dir, &dir, &v60, dist);
    if (v60.y < 0.0f) {
        dist *= -1.0f;
    }
    rot.y = WrapAngle_13c050(rot.y + dist);
    CharaSetYaw_2138f0(D_004DB92C[0], rot.y);
    if (arg1 >= n) {
        f = dist;
        f = (f < 0.0f) ? -f : f;
        if (f < D_0047D1DC) {
            ScriptSlotStoreFloatRef_2cc8e0(args, 0.0f);
        } else {
            ScriptSlotStoreFloatRef_2cc8e0(args, *(volatile f32 *)&dist);
        }
    }
    return 1;
}
