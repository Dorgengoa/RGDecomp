#include "types.h"

/* the 0x570 field is an `ld`, so it is 64 bits wide. */

extern s32 CharaSwimCanGrabLedge_20fa10(void *p);
extern s32 CharaPlayedMotionIsCurrent_2124c0(void *p);

s32 CharaSelectSwimState_21b110(void *p)
{
    if (CharaSwimCanGrabLedge_20fa10(p) != 0) {
        if (CharaPlayedMotionIsCurrent_2124c0(p) != 0) {
            return 100;
        }
    }
    if ((*(u64 *)((u8 *)p + 0x570) & 3) != 0) {
        return 1;
    }
    return 0;
}
