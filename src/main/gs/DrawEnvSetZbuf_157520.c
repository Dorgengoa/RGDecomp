#include "types.h"

typedef struct {
    u8 pad[0x38];
    s32 x38;
    u8 pad2[0x54];
    u16 a : 9;
    u16 r : 7;
    u8 b92;
    u8 c : 4;
    u8 d : 4;
} S;

void DrawEnvSetZbuf_157520(S *o, s32 a1, s32 a2, s32 a3, s32 a4)
{
    o->x38 = a4;
    o->a = a1;
    o->c = a4;
}
