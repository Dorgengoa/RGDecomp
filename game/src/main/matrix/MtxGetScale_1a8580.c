/* rgp:protos */
#define RGP_SELF_MtxGetScale_1a8580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z; s32 w; } V_001a8580;

/*rgp*/

void MtxGetScale_1a8580(void *p, V_001a8580 *out)
{
    out->x = VecLength_13d4a0(p);
    out->y = VecLength_13d4a0((void *)((s32)p + 0x10));
    out->z = VecLength_13d4a0((void *)((s32)p + 0x20));
    out->w = 0;
}
