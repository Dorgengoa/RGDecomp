/* rgp:protos */
#define RGP_SELF_MinimapBuildRectCornersMaybe_3252b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct F4 { f32 a, b, c, d; } F4;
extern F4 D_0047F430 __attribute__((section(".sdata")));
extern F4 D_0047F440 __attribute__((section(".sdata")));
extern F4 D_0047F450 __attribute__((section(".sdata")));
extern F4 D_0047F460 __attribute__((section(".sdata")));

void MinimapBuildRectCornersMaybe_3252b0(s32 unused, f32 *o0, f32 *o1, f32 *o2, f32 *o3, s32 x, s32 y, f32 *scale, f32 c, f32 s, u8 rot, s32 w, s32 h)
{
    Vec4 c0 __attribute__((aligned(16)));
    Vec4 c1 __attribute__((aligned(16)));
    Vec4 c2 __attribute__((aligned(16)));
    Vec4 c3 __attribute__((aligned(16)));
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    s32 k;

    *(F4 *)&c0 = D_0047F430;
    x0 = (f32)((1 - x) + w);
    y0 = (f32)((1 - y) + h);
    x1 = (f32)(x + w);
    y1 = (f32)(y + h);
    *(F4 *)&c1 = D_0047F440;
    *(F4 *)&c2 = D_0047F450;
    *(F4 *)&c3 = D_0047F460;
    c0.x = x0;
    c0.y = y0;
    c1.x = x1;
    c1.y = y0;
    c2.x = x0;
    c2.y = y1;
    c3.x = x1;
    c3.y = y1;
    if (rot != 0) {
        o0[0] = x0 * s - c0.y * c;
        o1[0] = x1 * s - c1.y * c;
        o2[0] = x0 * s - c2.y * c;
        o3[0] = x1 * s - c3.y * c;
        o0[1] = y0 * s + c0.x * c;
        o1[1] = y0 * s + c1.x * c;
        o2[1] = y1 * s + c2.x * c;
        o3[1] = y1 * s + c3.x * c;
    } else {
        k = 0;
        do {
            o0[k] = (&c0.x)[k];
            o1[k] = (&c1.x)[k];
            o2[k] = (&c2.x)[k];
            o3[k] = (&c3.x)[k];
            k++;
        } while (k < 3);
    }
    if (scale != 0) {
        k = 0;
        do {
            o0[k] *= scale[k];
            o1[k] *= scale[k];
            o2[k] *= scale[k];
            o3[k] *= scale[k];
            k++;
        } while (k < 2);
    }
}
