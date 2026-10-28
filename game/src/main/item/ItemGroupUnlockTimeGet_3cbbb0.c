/* rgp:protos */
#define RGP_SELF_ItemGroupUnlockTimeGet_3cbbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T_003cbbb0 {
    u8 pad000[0x880];
    double arr880[64];
};

double ItemGroupUnlockTimeGet_3cbbb0(struct T_003cbbb0 *p0, s32 p1)
{
    if (p1 < 0) {
        goto fail;
    }
    if (p1 < 0x40) {
        goto ok;
    }
fail:
    return -1.0;
ok:
    return p0->arr880[p1];
}
