/* rgp:protos */
#define RGP_SELF_DrawCtxCallTagCacheClear_13fd40 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawCtxCallTagCacheClear_13fd40(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x3C48) = 0;
        l0 = ((l1 + 1) < 0x20);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
