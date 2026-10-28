/* rgp:protos */
#define RGP_SELF_BitArray64Test_32c340 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 BitArray64Test_32c340(s32 p0, s32 p1)
{
    s64 t0;

    t0 = *(s64 *)((u8 *)p0 + ((((u32)p1) >> 6) << 3));
    return (((((s64)1) << (p1 & 0x3F)) & t0) != 0);
}
