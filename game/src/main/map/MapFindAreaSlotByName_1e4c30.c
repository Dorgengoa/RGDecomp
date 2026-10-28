/* rgp:protos */
#define RGP_SELF_MapFindAreaSlotByName_1e4c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Same four-slot walk as the FUN_001e455x family, but the probe is a pair:
   fetch the slot's handle, then test it.  Returns the SLOT, not the test
   result -- `daddu $2,$17,$0` in the exit branch's delay slot. */

void *MapFindAreaSlotByName_1e4c30(void *p0, s32 key)
{
    u8 *p;
    s32 i;

    if (key == 0) {
        return 0;
    }
    p = (u8 *)p0 + 0x1928;
    i = 0;
    while (i < 4) {
        if (((unsigned char)StrEqualNonNull_1ca6c0(MapDataGetName_1e7bf0(p), key)) != 0) {
            return p;
        }
        i++;
        p += 0x1CC;
    }
    return 0;
}
