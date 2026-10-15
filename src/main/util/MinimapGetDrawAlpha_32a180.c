#include "types.h"

typedef struct {
    u8 pad000[0xEC];
    f32 fEC;
    f32 fF0;
    u8 pad0F4[0x11C - 0xF4];
    s8 f11C;
} T_0032a180;

f32 MinimapGetDrawAlpha_32a180(T_0032a180 *p)
{
    switch (p->f11C) {
    case 2:
        return 1.0f;
    case 1:
        break;
    case 0:
        break;
    default:
        break;
    }
    return p->fEC * p->fF0;
}
