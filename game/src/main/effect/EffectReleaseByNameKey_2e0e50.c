/* rgp:protos */
#define RGP_SELF_EffectReleaseByNameKey_2e0e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(s32, s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EffectReleaseByNameKey_2e0e50(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 l1;
    s32 t0;
    s32 rv6;
    s32 t1;
    s32 rv5;
    s32 r2;
    s32 rv4;
    s32 t2;
    s32 r3;
    s32 r7;

    l1 = 0;
    do {
        t0 = *(s32 *)((u8 *)p0 + (((l1 << 3) - l1) << 4) + 0x174);
        rv6 = t0;
        if (t0 >= 0) {
            t1 = *(s32 *)((u8 *)p0 + (((l1 << 3) - l1) << 4) + 0x1D4);
            rv5 = t1;
            if (t1 >= 0) {
                r2 = strcmp(((p0 + (((l1 << 3) - l1) << 4)) + 0x1A4), p1);
                rv4 = r2;
                if (r2 == 0) {
                    t2 = *(s32 *)((u8 *)p0 + (((l1 << 3) - l1) << 4) + 0x178);
                    r3 = (EffDefDestroyInstancesByTag_19ff40((p0 + 0x58), t2, p2), (s32)0);
                    rv4 = r3;
                }
                rv5 = rv4;
            }
            rv6 = rv5;
        }
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
    r7 = (EffectEntriesReleaseNodesByNameTag_2de890((p0 + 0x1674), p1, p2), (s32)0);
    return r7;
}
