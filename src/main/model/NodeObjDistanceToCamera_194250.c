#include "types.h"
#include "vec.h"

void VecSub_13be40(Vec4 *out, const Vec4 *a, const Vec4 *b);      /* extern: out = a - b */
void MtxMulPoint_13c890(Vec4 *out, const Mtx4 *m, const Vec4 *v);      /* extern: out = m * v */
void MtxInverse_13cf40(Mtx4 *out, const Mtx4 *in);                    /* extern, asm */
void VecMax_13dfe0(Vec4 *out, const Vec4 *a, const Vec4 *b);      /* extern, asm: componentwise max */
void CameraGetEyePos_13fce0(void *o, u128 *out);                           /* extern */
s32 GetDrawCtx_15de80(void);                                          /* extern */
f32 NodeDistanceToCamera_185f00(void *p);                                       /* extern */
void NodeCalcWorldMatrix_186130(void *o, Mtx4 *out);                           /* extern */

f32 NodeObjDistanceToCamera_194250(u8 *arg0) {
    u128 sp90;
    Mtx4 sp50;
    Vec4 sp40;
    Vec4 sp30;
    Vec4 sp20;
    f32 var_f0;
    f32 var_f1;

    if ((*(s32 *)(arg0 + 0x44)) == 0) {
        return NodeDistanceToCamera_185f00(arg0);
    }
    CameraGetEyePos_13fce0((void *)GetDrawCtx_15de80(), &sp90);
    NodeCalcWorldMatrix_186130(arg0, &sp50);
    MtxInverse_13cf40(&sp50, &sp50);
    MtxMulPoint_13c890((Vec4 *)&sp90, &sp50, (Vec4 *)&sp90);
    VecSub_13be40(&sp40, (Vec4 *)&sp90, (Vec4 *)(arg0 + 0xB0));
    VecSub_13be40(&sp30, (Vec4 *)(arg0 + 0xC0), (Vec4 *)&sp90);
    VecMax_13dfe0(&sp20, &sp40, &sp30);
    var_f1 = sp20.y;
    var_f0 = sp20.x;
    if (var_f0 > var_f1) {
        var_f0 = (var_f0 > sp20.z) ? var_f0 : sp20.z;
    } else {
        var_f0 = (var_f1 > sp20.z) ? var_f1 : sp20.z;
    }
    if (var_f0 < 0.0f) {
        var_f0 = 0.0f;
    }
    return var_f0;
}
