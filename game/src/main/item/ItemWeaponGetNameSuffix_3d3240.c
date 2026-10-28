/* rgp:protos */
#define RGP_SELF_ItemWeaponGetNameSuffix_3d3240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00465BC0[];

typedef struct S_003D3240 {
    u8 pad1C[0x1C];
    s8 f1C;
} S_003D3240;

s32 *ItemWeaponGetNameSuffix_3d3240(S_003D3240 *self)
{
    s8 n = self->f1C;
    if (n <= 0) goto zero;
    if (n < 7) goto ok;
zero:
    return 0;
ok:
    return &D_00465BC0[n];
}
