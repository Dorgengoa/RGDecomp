/* rgp:protos */
#define RGP_SELF_InsectModelMemCtor_31a550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectModelMemCtor_31a550(s32 p0)
{
    u8 *l1;

    MemStackCtor_14e030((p0 + 4));
    l1 = (u8 *)p0 + 0x64;
    do {
        MemStackCtor_14e030((s32)l1);
        l1 = l1 + 0x5C;
    } while (l1 < (u8 *)p0 + 0x3FC);
    return p0;
}
