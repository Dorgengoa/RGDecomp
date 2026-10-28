/* rgp:protos */
#define RGP_SELF_SoundBankClearIds_1b9ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SoundBankClearIds_1b9ed0(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 3) + 0x160) = -1;
        l0 = ((l1 + 1) < 0x10);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
