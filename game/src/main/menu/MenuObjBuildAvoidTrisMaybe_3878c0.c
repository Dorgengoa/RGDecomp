/* rgp:protos */
#define RGP_SELF_MenuObjBuildAvoidTrisMaybe_3878c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Q_003878c0 { u128 v; } Q_003878c0;

typedef struct S_003878c0 {
    u8 pad180[0x180];
    Q_003878c0 f180;
    u8 pad190[0x985 - 0x190];
    s8 f985;
} S_003878c0;

/*rgp*/

s32 MenuObjBuildAvoidTrisMaybe_3878c0(S_003878c0 *self, void *b, s32 c, void *rgp_a3)
{
    u128 tmp;
    if (self->f985 != 0) goto g1;
    return 0;
g1:
    if (b == 0) goto zero;
    if (c > 0) goto ok;
zero:
    return 0;
ok:
    tmp = self->f180.v;
    return CollBuildWallTrisMaybe_16d550(b, c, &tmp, (void *)rgp_a3, 2.0f, 2.0f);
}
