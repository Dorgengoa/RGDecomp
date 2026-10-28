/* rgp:protos */
#define RGP_SELF_ObjRecUpdateDistLightMaybe_319f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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


void ObjRecUpdateDistLightMaybe_319f60(void *p, void *q, s32 k)
{
    u8 outv[0x10] __attribute__((aligned(16)));
    f32 a[16] __attribute__((aligned(16)));
    f32 b[16] __attribute__((aligned(16)));
    f32 c[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    u8 *r;
    u8 *m;

    if (ObjRecIsDrawableMaybe_1c48b0(p, k) == 0) {
        return;
    }
    r = ((u8 *)ObjRecGetLiveObject_1c4a90(p, k));
    if (r == 0) {
        return;
    }
    m = ((u8 *)ParamTableGetRec_1cfbc0(p, k));
    if (m == 0) {
        return;
    }
    if (ObjGetNthAttachPointPosSafe_23b0c0(r, 0, 0, outv) == 0) {
        FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(r), outv);
    }
    *(f32 *)(m + 0xC) = VecDist_1cb420(q, outv);
    ParamTableSetAlpha_1cfb10(p, k, *(f32 *)(r + 0x448));
    a[0] = 0.0f;
    a[1] = 1.0f;
    a[2] = 0.0f;
    a[3] = 0.0f;
    a[4] = 0.0f;
    a[5] = 1.0f;
    a[6] = 0.0f;
    a[7] = 0.0f;
    a[8] = 0.0f;
    a[9] = 1.0f;
    a[10] = 0.0f;
    a[11] = 0.0f;
    a[12] = 0.0f;
    a[13] = 1.0f;
    a[14] = 0.0f;
    a[15] = 0.0f;
    b[0] = 0.0f;
    b[1] = 0.0f;
    b[2] = 0.0f;
    b[3] = 128.0f;
    b[4] = 0.0f;
    b[5] = 0.0f;
    b[6] = 0.0f;
    b[7] = 128.0f;
    b[8] = 0.0f;
    b[9] = 0.0f;
    b[10] = 0.0f;
    b[11] = 128.0f;
    b[12] = 0.0f;
    b[13] = 0.0f;
    b[14] = 0.0f;
    b[15] = 128.0f;
    c[0] = 128.0f;
    c[1] = 128.0f;
    c[2] = 128.0f;
    c[3] = 128.0f;
    d[0] = 128.0f;
    d[1] = 128.0f;
    d[2] = 128.0f;
    d[3] = 128.0f;
    ObjRecGetFlags_1c3d90(p, 1, k);
    Character2LightBlendSetTarget_1aebe0(r, 0, a, b, c, d, 0);
}
