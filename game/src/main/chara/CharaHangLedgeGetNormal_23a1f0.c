/* rgp:protos */
#define RGP_SELF_CharaHangLedgeGetNormal_23a1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 CharaHangLedgeGetNormal_23a1f0(u8 *base, void *dst, s32 i)
{
    if (i < 0) goto fail;
    if (i < 2) goto ok;
fail:
    return 0;
ok:
    VecCopy_1cbe30(dst, base + i * 16 + 0x40);
    return 1;
}
