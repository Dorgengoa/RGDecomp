/* rgp:protos */
#define RGP_SELF_VariantPoolReset_3e01f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S003e01f0 {
    u8 pad[0xE08];
    s16 hE08;
    s16 hE0A;
    u8 bit0 : 1;
    u8 rest : 7;
} S003e01f0;

s32 VariantPoolReset_3e01f0(S003e01f0 *s)
{
    s->hE08 = 0;
    s->hE0A = 0;
    s->bit0 = 0;
    return 1;
}
