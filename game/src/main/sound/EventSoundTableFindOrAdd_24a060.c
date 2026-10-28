/* rgp:protos */
#define RGP_SELF_EventSoundTableFindOrAdd_24a060 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventSoundTableFindOrAdd_24a060(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 l1;
    s32 t0;
    s32 t1;
    s32 l2;
    s32 t2;

    l1 = 0;
    while (l1 < 0x40) {
        t0 = *(s32 *)((u8 *)p0 + (l1 * 0x14));
        if (p1 == t0) {
            t1 = *(s32 *)((u8 *)p0 + (l1 * 0x14) + 0x4);
            if (p2 == t1) {
                return (p0 + (l1 * 0x14));
            }
        }
        l0 = (p0 + (l1 * 0x14));
        l1 = (l1 + 1);
    }
    l2 = 0;
    while (l2 < 0x40) {
        t2 = *(s32 *)((u8 *)p0 + (l2 * 0x14));
        if (t2 == -1) {
            *(s32 *)((u8 *)p0 + (l2 * 0x14)) = p1;
            *(s32 *)((u8 *)p0 + (l2 * 0x14) + 0x4) = p2;
            return (p0 + (l2 * 0x14));
        }
        l2 = (l2 + 1);
    }
    return 0;
}
