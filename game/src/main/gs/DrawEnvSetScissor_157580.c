/* rgp:protos */
#define RGP_SELF_DrawEnvSetScissor_157580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct BF00157580 {
    __extension__ unsigned short v : 11;
    unsigned short r : 5;
} __attribute__((aligned(2))) BF00157580;

typedef struct Obj00157580 {
    u8 pad0[0xB0];
    BF00157580 b0;
    BF00157580 b2;
    BF00157580 b4;
    BF00157580 b6;
} Obj00157580;

void DrawEnvSetScissor_157580(Obj00157580 *self, s32 x, s32 y, s32 z, s32 w)
{
    self->b0.v = x;
    self->b2.v = z;
    self->b4.v = y;
    self->b6.v = w;
}
