/* rgp:protos */
#define RGP_SELF_InsectRecSlotGetItem_3cfb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004838E8;

typedef struct P_003cfb30 {
    u8 padC[0xC];
    s32 arr[1];
} P_003cfb30;

typedef struct S_003cfb30 {
    u8 pad18[0x18];
    P_003cfb30 *f18;
} S_003cfb30;

s32 InsectRecSlotGetItem_3cfb30(S_003cfb30 *self, s32 i)
{
    if (D_004838E8 != 0) goto g1;
    return 0;
g1:
    if (i < 0) goto zero;
    if (i < 5) goto ok;
zero:
    return 0;
ok:
    return self->f18->arr[i];
}
