#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V00333520 __attribute__((aligned(16)));

typedef struct {
    V00333520 r[4];
} M00333520;

typedef struct {
    f32 x, y;
    s32 z;
} R00333520;

extern f32 sqrtf(f32 x);
void MtxMulVec4_10a8c0(V00333520 *, M00333520 *, V00333520 *);
f32 Atan2f_1291a8(f32, f32);
void VecNormalize_13bd90(V00333520 *, V00333520 *);
f32 WrapAngle_13c050(f32);
void FrameCalcWorldMatrix_148ff0(s32, M00333520 *);
s32 ModelGetFrame_1511f0(s32, s32);
s32 ModelFindFrameIndexByName_151220(s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetCurrentScene_1f5be0(void);
void ScriptSlotStoreVec3_334790(s32, R00333520 *);
s32 ScriptSlotGetCodeAddr_334870(s32);
s32 ScriptSlotGetInt_3348b0(s32);

s32 ScriptCmdGetNodeAngles_333520(s64 *arg0, s32 arg1) {
    V00333520 v;
    M00333520 m;
    R00333520 r;
    s32 a;
    s32 b;
    s32 h;

    if (arg1 != 5) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0((s32)arg0++);
    b = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    h = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a);
    if (h == 0) {
        return 0;
    }
    h = ModelGetFrame_1511f0(h, ModelFindFrameIndexByName_151220(h, b));
    if (h == 0) {
        return 0;
    }
    FrameCalcWorldMatrix_148ff0(h, &m);
    m.r[3].x = 0.0f;
    m.r[3].y = 0.0f;
    m.r[3].z = 0.0f;
    m.r[3].w = 1.0f;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    v.w = 1.0f;
    MtxMulVec4_10a8c0(&v, &m, &v);
    VecNormalize_13bd90(&v, &v);
    r.x = WrapAngle_13c050(-Atan2f_1291a8(v.y, sqrtf(v.x * v.x + v.z * v.z)));
    r.y = WrapAngle_13c050(Atan2f_1291a8(v.x, v.z));
    r.z = 0;
    ScriptSlotStoreVec3_334790((s32)arg0, &r);
    return 1;
}
