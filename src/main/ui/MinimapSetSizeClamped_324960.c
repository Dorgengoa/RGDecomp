#include "types.h"
typedef struct S00324960 {
    u8 pad[0x108];
    s16 h108;
    s16 h10A;
} S00324960;

void MinimapSetSizeClamped_324960(S00324960 *s, s32 w, s32 h)
{
    if (w >= 0x1E0) {
        w = 0x1E0;
    }
    if (h >= 0x1A0) {
        h = 0x1A0;
    }
    s->h108 = w;
    s->h10A = h;
}
