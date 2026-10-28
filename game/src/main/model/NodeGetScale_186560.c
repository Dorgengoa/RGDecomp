/* rgp:protos */
#define RGP_SELF_NodeGetScale_186560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z; s32 w; } V4;

typedef struct {
    u8 pad00[0x18];
    f32 m18;
    f32 m1C;
    f32 m20;
    u8 pad24[0x0C];
    s16 m30;
} Obj_186560;

/*rgp*/

void NodeGetScale_186560(Obj_186560 *p, V4 *out)
{
    if (p->m30 != 0) {
        VecSetOnes_13e180(out);
    } else {
        out->x = p->m18;
        out->y = p->m1C;
        out->z = p->m20;
        out->w = 0;
    }
}
