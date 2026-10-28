/* rgp:protos */
#define RGP_SELF_CollFindGroundTriMaybe_23af50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V0023AF50;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B080[0x400];
extern f32 D_0047DAC4;
extern f32 D_0047DB14;

s32 CollFindGroundTriMaybe_23af50(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 *arg5)
{
    V0023AF50 v __attribute__((aligned(16)));
    u8 buf[0x80] __attribute__((aligned(16)));
    f32 d;
    f32 a;
    f32 z;
    s32 best;
    s32 i;

    if (arg0 == NULL || arg1 <= 0) {
        return -1;
    }
    VecCopy_1cbe30(&v, arg3);
    d = *(f32 *)D_0045B080;
    d = 5.0f * (D_0047DB14 * d);
    v.y += d;
    CollSweepInit_1c81b0(buf, &v, arg4, d, 1.0f);
    best = -1;
    for (i = 0; i < arg1; i++, arg0 += 0x60) {
        if ((*(s16 *)(arg0 + 0x46) & arg2) == 0) {
            a = *(f32 *)(arg0 + 0x34);
            a = (a < 0.0f) ? -a : a;
            d = FloatOutOfRange_1c9210(a, D_0047DAC4, 1.0f);
            z = 0.0f;
            if (d == z && CollSweepTri_1c7790(buf, arg0, arg0 + 0x10, arg0 + 0x20) != 0) {
                best = i;
            }
        }
    }
    if (best < 0) {
        return -1;
    }
    if (arg5 != NULL) {
        *arg5 = *(f32 *)(buf + 0x24);
    }
    return best;
}
