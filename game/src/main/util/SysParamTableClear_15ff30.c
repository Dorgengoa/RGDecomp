/* rgp:protos */
#define RGP_SELF_SysParamTableClear_15ff30 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SysParamTableClear_15ff30(s32 p0)
{
    s32 l0;
    s32 l1;
    s32 l2;
    s32 l3;

    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 3) + 0x14) = 0;
        l0 = ((l1 + 1) < 0x80);
        l1 = (l1 + 1);
    } while (l0 != 0);
    l2 = l0;
    l3 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l3 << 3) + 0x414) = 0;
        l2 = ((l3 + 1) < 0x20);
        l3 = (l3 + 1);
    } while (l2 != 0);
}
