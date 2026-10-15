#include "types.h"

typedef struct Obj_0026f1b0 {
    u8 pad000[0x10];
    u8 v[4];
} Obj_0026f1b0;

void TextStyleSetGradRgbaQuad_26f1b0(Obj_0026f1b0 *o, u64 c)
{
    o->v[0] = ((u8 *)&c)[0];
    o->v[1] = ((u8 *)&c)[1];
    o->v[2] = ((u8 *)&c)[2];
    o->v[3] = ((u8 *)&c)[3];
}
