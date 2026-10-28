/* rgp:protos */
#define RGP_SELF_VecAngleXZ_1cbe60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
} V3;

/*rgp*/

f32 VecAngleXZ_1cbe60(V3 *a, V3 *b)
{
    f32 bx;
    f32 ax;
    f32 bz;
    f32 az;

    bx = b->x;
    ax = a->x;
    bz = b->z;
    az = a->z;
    return Atan2f_1291a8(az * bx - ax * bz, az * bz + ax * bx);
}
