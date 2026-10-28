/* rgp:protos */
#define RGP_SELF_SplineGetPos_257160 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

/* Copy a world object's position out as a homogeneous point.

   ★ The w is stored as an INTEGER -- retail materialises 0x3F800000 with a
   `lui` and an `sw`, not an `lwc1`/`swc1` pair -- which is just what mwcc does
   for a float constant assigned to a member whose neighbours are already
   float-loaded. Writing 1.0f is enough; naming it as an extern is not needed
   here because the constant never reaches the FPU. */

typedef struct Positioned {
    u8 pad000[0x38C];
    f32 x, y, z;       /* +0x38C */
} Positioned;

void SplineGetPos_257160(Positioned *o, Vec4 *out)
{
    out->x = o->x;
    out->y = o->y;
    out->z = o->z;
    out->w = 1.0f;
}
