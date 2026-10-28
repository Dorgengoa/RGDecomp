/* rgp:protos */
#define RGP_SELF_CharaSelectSwimState_21b110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* the 0x570 field is an `ld`, so it is 64 bits wide. */

/*rgp*/
/*rgp*/

s32 CharaSelectSwimState_21b110(void *p)
{
    if (CharaSwimCanGrabLedge_20fa10(p) != 0) {
        if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0) {
            return 100;
        }
    }
    if ((*(u64 *)((u8 *)p + 0x570) & 3) != 0) {
        return 1;
    }
    return 0;
}
