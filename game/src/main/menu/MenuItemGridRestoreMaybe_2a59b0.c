/* rgp:protos */
#define RGP_SELF_MenuItemGridRestoreMaybe_2a59b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memcpy(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MenuItemGridRestoreMaybe_2a59b0(s32 p0, s32 p1)
{
    if (p1 != 0) {
        memcpy((p0 + 0x10), p1, 0x60);
    }
}
