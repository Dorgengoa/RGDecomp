/* rgp:protos */
#define RGP_SELF_MenuTransdataRelease_206260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BF8;
extern u8 D_004BBF80[];

void MenuTransdataRelease_206260(void)
{
    RecStackSlotRelease_201d10(D_004BBF80, &D_00481BF8);
}
