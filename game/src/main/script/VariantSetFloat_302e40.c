/* rgp:protos */
#define RGP_SELF_VariantSetFloat_302e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void VariantSetFloat_302e40(u8 *p, f32 v)
{
    f32 t;

    t = v;
    p[0] = 1;
    p[1] = ((u8 *)&t)[0];
    p[2] = ((u8 *)&t)[1];
    p[3] = ((u8 *)&t)[2];
    p[4] = ((u8 *)&t)[3];
}
