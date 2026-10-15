#include "types.h"

extern void DrawListAddVramCopy_1414a0(s32, s32, s32 *, s32, s32, s32, s32);

typedef struct V1417 { s32 x, y, z, w; } V1417;

void DrawListAddVramCopyFixed_1417b0(s32 arg0, s32 arg1, V1417 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    V1417 v;

    arg4 >>= 4;
    arg5 >>= 4;
    v.x = arg2->x;
    v.y = arg2->y;
    v.z = arg2->z;
    v.w = arg2->w;
    v.y = arg2->y >> 4;
    v.w = arg2->w >> 4;
    v.x = arg2->x >> 4;
    v.z = arg2->z >> 4;
    DrawListAddVramCopy_1414a0(arg0, arg1, (s32 *)&v, arg3, arg4, arg5, arg6);
}
