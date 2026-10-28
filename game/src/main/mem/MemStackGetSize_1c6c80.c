/* rgp:protos */
#define RGP_SELF_MemStackGetSize_1c6c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MemStackGetSize_1c6c80(u8 *a0)
{
    s32 l1c;
    s32 l18;
    s32 l14;
    s32 l10;

    if (a0 == 0) {
        return 0;
    }
    {
        u8 ok = *(s32 *)(a0 + 0x28) != 0;
        if (ok) {
            return *(s32 *)(a0 + 0x34);
        }
    }
    if (*(s32 *)(a0 + 0x14) == 0) {
        return 0;
    }
    MemStackGetStats_14d0e0(a0, &l1c, &l18, &l14, &l10);
    return l1c + l18;
}
