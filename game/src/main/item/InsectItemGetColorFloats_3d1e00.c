/* rgp:protos */
#define RGP_SELF_InsectItemGetColorFloats_3d1e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

s32 InsectItemGetColorFloats_3d1e00(void *arg0, f32 *arg1)
{
    s32 temp_7;
    f32 x, y;
    s32 a, b, c, d;

    temp_7 = *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 0x2C);
    b = (temp_7 >> 0x10) & 0xF;
    c = (temp_7 >> 8) & 0xF;
    d = temp_7 & 0xF;
    a = (temp_7 >> 0x18) & 0xF;
    x = (f32)a / 256.0f;
    y = (f32)b / 256.0f;
    arg1[0] = x;
    arg1[1] = y;
    arg1[2] = (f32)c / 256.0f;
    arg1[3] = (f32)d / 256.0f;
    return *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x18) + 0x2C);
}
