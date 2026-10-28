/* rgp:protos */
#define RGP_SELF_ItemSpecialWeaponLoadState_3d2790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S3d2790 { u8 pad000[0x26]; s16 m26; };

/*rgp*/

s32 ItemSpecialWeaponLoadState_3d2790(struct S3d2790 *p, void *a, s32 b, int rgp_a3)
{
    s32 r;

    if (a == 0) goto fail;
    if (b > 0) goto ok;
fail:
    return 0;
ok:
    r = InvObjLoadStateChecked_3d30d0(p, a, b, (int)rgp_a3);
    p->m26 = 0;
    return r;
}
