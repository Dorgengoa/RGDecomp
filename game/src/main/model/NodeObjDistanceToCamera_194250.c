/* rgp:protos */
#define RGP_SELF_NodeObjDistanceToCamera_194250 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/      /* extern: out = a - b */
/*rgp*/      /* extern: out = m * v */
/*rgp*/                    /* extern, asm */
/*rgp*/      /* extern, asm: componentwise max */
/*rgp*/                           /* extern */
/*rgp*/                                          /* extern */
/*rgp*/                                       /* extern */
/*rgp*/                           /* extern */

f32 NodeObjDistanceToCamera_194250(u8 *arg0) {
    u128 sp90;
    Mtx4 sp50 __attribute__((aligned(16)));
    Vec4 sp40 __attribute__((aligned(16)));
    Vec4 sp30 __attribute__((aligned(16)));
    Vec4 sp20 __attribute__((aligned(16)));
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
