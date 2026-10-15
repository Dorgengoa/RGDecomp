#include "types.h"
typedef struct { f32 w[4]; } SD4_0047EFC0;
extern SD4_0047EFC0 D_0047EFC0 __attribute__((section(".sdata")));


void CharaPlaceAt_2f3a40(void *self, f32 *buf, s32 count, f32 d);

void CharaPlaceAtXyz_2f39f0(void *self, s32 count, f32 a, f32 b, f32 c, f32 d)
{
    f32 buf[4];

    *(SD4_0047EFC0 *)buf = D_0047EFC0;
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    CharaPlaceAt_2f3a40(self, buf, count, d);
}
