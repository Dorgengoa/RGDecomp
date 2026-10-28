/* rgp:protos */
#define RGP_SELF_NodeObjIsInViewUnoccludedMaybe_194100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NodeObjIsInViewUnoccludedMaybe_194100(u8 *arg0, s32 arg1, s32 arg2)
{
    Mtx4 m __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    f32 w;
    s32 i;

    if (*(s32 *)(arg0 + 0xA8) == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(arg0, &m);
    if (CameraBoxInViewStub_15cd00() == 0) {
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
        if (((unsigned char)OcclusionPlaneHidesSphereMaybe_1970b0(arg1, &v)) != 0) {
            return 0;
        }
    }
    return 1;
}
