#include "types.h"

struct S3d2790 { u8 pad000[0x26]; s16 m26; };

extern s32 InvObjLoadStateChecked_3d30d0(struct S3d2790 *, void *, s32);

s32 ItemSpecialWeaponLoadState_3d2790(struct S3d2790 *p, void *a, s32 b)
{
    s32 r;

    if (a == 0) goto fail;
    if (b > 0) goto ok;
fail:
    return 0;
ok:
    r = InvObjLoadStateChecked_3d30d0(p, a, b);
    p->m26 = 0;
    return r;
}
