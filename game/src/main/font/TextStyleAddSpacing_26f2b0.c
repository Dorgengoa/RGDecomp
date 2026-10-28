/* rgp:protos */
#define RGP_SELF_TextStyleAddSpacing_26f2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S0026f2b0 {
    u8 pad[0x1A];
    s16 h1A;
    s16 h1C;
} S0026f2b0;

void TextStyleAddSpacing_26f2b0(S0026f2b0 *s, s32 dx, s32 dy)
{
    s->h1A += (s16)dx;
    s->h1C += (s16)dy;
}
