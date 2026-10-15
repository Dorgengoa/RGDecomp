#include "types.h"
typedef struct S0014a730 {
    u8 pad[0x26];
    s16 h26;
    u8 pad28[0x2D - 0x28];
    u8 b2D;
} S0014a730;

void ModelFrameOrFlags_14a730(S0014a730 *s, s32 m)
{
    s16 v;

    v = s->h26 | m;
    s->h26 = v;
    if ((v & 0x10) != 0) {
        s->b2D = 1;
    }
}
