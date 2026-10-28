/* rgp:protos */
#define RGP_SELF_McCardIsReady_376280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_00376280 {
    s32 f0;
    s32 f4;
    u8 pad8[0x10];
    s32 f18;
} S_00376280;

s32 McCardIsReady_376280(S_00376280 *a, void *b)
{
    if (a != 0) goto g1;
    return 0;
g1:
    if (a->f0 == 0) goto zero;
    if (a->f4 == 2) goto ok;
zero:
    return 0;
ok:
    if (b != 0) {
        if (a->f18 != 0) return 0;
    }
    return 1;
}
