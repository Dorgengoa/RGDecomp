/* rgp:protos */
#define RGP_SELF_InsectCageMgrReleaseAll_39a2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void InsectCageMgrReleaseAll_39a2e0(u8 *p)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        InsectCageSlotRelease_39b9c0(p + i * 48);
    }
}
