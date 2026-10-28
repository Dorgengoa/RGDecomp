/* rgp:protos */
#define RGP_SELF_DrawEnvSetZbuf_157520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x38];
    s32 x38;
    u8 pad2[0x54];
    __extension__ unsigned short a : 9;
    unsigned short r : 7;
    u8 b92;
    u8 c : 4;
    u8 d : 4;
} __attribute__((aligned(2))) S;

void DrawEnvSetZbuf_157520(S *o, s32 a1, s32 a2, s32 a3, s32 a4)
{
    o->x38 = a4;
    o->a = a1;
    o->c = a4;
}
