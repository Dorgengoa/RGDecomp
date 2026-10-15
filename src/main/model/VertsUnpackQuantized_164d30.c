#include "types.h"
#include "vec.h"

void VertsUnpackQuantized_164d30(f32 *arg0, void *arg1, s32 arg2, s32 arg3, u128 *arg4)
{
    Vec4 s;
    s32 i;
    f32 sc;
    f32 sx, sy, sz;

    *(u128 *)&s = *arg4;
    if (arg3 == 32) {
        f32 *src = arg1;
        for (i = 0; i < arg2; ) {
            i++;
            arg0[0] = src[0];
            arg0[1] = src[1];
            arg0[2] = src[2];
            src += 3;
            ((s32 *)arg0)[3] = 0;
            arg0 += 4;
        }
    } else if (arg3 == 16) {
        s16 *src = arg1;
        sc = 0.000030517578f;
        for (i = 0; i < arg2; ) {
            i++;
            arg0[0] = 0.000030517578f * (f32)src[0] * s.x;
            arg0[1] = 0.000030517578f * (f32)src[1] * s.y;
            arg0[2] = 0.000030517578f * (f32)src[2] * s.z;
            src += 3;
            ((s32 *)arg0)[3] = 0;
            arg0 += 4;
        }
    } else if (arg3 == 8) {
        s8 *src = arg1;
        sc = 0.0078125f;
        for (i = 0; i < arg2; ) {
            i++;
            arg0[0] = 0.0078125f * (f32)src[0] * s.x;
            arg0[1] = 0.0078125f * (f32)src[1] * s.y;
            arg0[2] = 0.0078125f * (f32)src[2] * s.z;
            src += 3;
            ((s32 *)arg0)[3] = 0;
            arg0 += 4;
        }
    }
}
