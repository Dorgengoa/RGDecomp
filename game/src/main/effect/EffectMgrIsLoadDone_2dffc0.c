/* rgp:protos */
#define RGP_SELF_EffectMgrIsLoadDone_2dffc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EffectMgrIsLoadDone_2dffc0(s32 p0)
{
    s32 l0;
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 r2;

    l0 = 0;
    while (l0 < 0x30) {
        t0 = *(s32 *)((u8 *)p0 + (((l0 << 3) - l0) << 4) + 0x174);
        rv1 = t0;
        if (t0 >= 0) {
            t1 = *(s32 *)((u8 *)p0 + (((l0 << 3) - l0) << 4) + 0x1D0);
            if (t1 == 0) {
                return 0;
            }
            rv1 = t1;
        }
        l0 = (l0 + 1);
    }
    r2 = ((unsigned short)EffectEntriesAllLoaded_2de760((p0 + 0x1674)));
    return (r2 & 0xFF);
}
