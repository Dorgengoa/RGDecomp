#include "types.h"
#include "vec.h"

extern s32 MtxMulVec4_13c900(Vec4 *, Mtx4 *, Vec4 *);
extern s32 MtxMul_13d240(Mtx4 *, s32, Mtx4 *);
extern s32 NodeCalcWorldMatrix_186130(u8 *, Mtx4 *);
extern s32 CameraBoxInViewStub_15cd00(u8 *, Mtx4 *);
extern s32 GetDrawCtxCamera_15de60(void);
extern s32 OcclusionPlaneHidesSphereMaybe_1970b0(s32, Vec4 *);

s32 NodeObjIsInViewUnoccludedMaybe_194100(u8 *arg0, s32 arg1, s32 arg2)
{
    Mtx4 m;
    Vec4 v;
    f32 w;
    s32 i;

    if (*(s32 *)(arg0 + 0xA8) == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(arg0, &m);
    if (CameraBoxInViewStub_15cd00(arg0 + 0xB0, &m) == 0) {
        return 0;
    }
    if (arg2 <= 0) {
        return 1;
    }
    MtxMul_13d240(&m, GetDrawCtxCamera_15de60() + 0xB0, &m);
    v = *(Vec4 *)(arg0 + 0xD0);
    w = *(f32 *)(arg0 + 0xDC);
    v.w = 1.0f;
    MtxMulVec4_13c900(&v, &m, &v);
    v.w = w;
    for (i = 0; i < arg2; i++, arg1 += 0xC0) {
        if (OcclusionPlaneHidesSphereMaybe_1970b0(arg1, &v) != 0) {
            return 0;
        }
    }
    return 1;
}
