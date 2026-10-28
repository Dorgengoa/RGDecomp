/* rgp:protos */
#define RGP_SELF_EffectEntriesDraw_2deac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EffectEntriesDraw_2deac0(s32 p0)
{
    s32 l0;
    s32 l1;
    s16 t0;

    l1 = 0;
    do {
        t0 = *(s16 *)((u8 *)p0 + (((l1 << 3) - l1) << 5) + 0xB4);
        if (t0 == 3) {
            EffectEntryDrawNodes_2da850((p0 + (((l1 << 3) - l1) << 5)));
        }
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
