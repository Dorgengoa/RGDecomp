/* rgp:protos */
#define RGP_SELF_EventVolumeWorldToLocal_2e5060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Mat0044 {
    f32 pad0;
    f32 rot[3][3];
    f32 trans[3];
} Mat0044;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

void EventVolumeWorldToLocal_2e5060(Mat0044 *arg0, Vec4 *arg1, Vec4 *arg2)
{
    Vec4 tmp __attribute__((aligned(16))) = {0};
    f32 w;
    f32 dx;
    f32 dy;
    f32 dz;

    w = arg2->w;
    dx = arg2->x - w * arg0->trans[0];
    dy = arg2->y - w * arg0->trans[1];
    dz = arg2->z - w * arg0->trans[2];
    tmp.w = w;
    arg1->x = arg0->rot[0][0] * dx + arg0->rot[0][1] * dy + arg0->rot[0][2] * dz;
    arg1->y = arg0->rot[1][0] * dx + arg0->rot[1][1] * dy + arg0->rot[1][2] * dz;
    arg1->z = arg0->rot[2][0] * dx + arg0->rot[2][1] * dy + arg0->rot[2][2] * dz;
    tmp.x = dx;
    tmp.y = dy;
    tmp.z = dz;
    arg1->w = w;
}
