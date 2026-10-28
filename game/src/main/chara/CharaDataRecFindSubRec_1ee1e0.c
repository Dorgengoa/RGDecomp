/* rgp:protos */
#define RGP_SELF_CharaDataRecFindSubRec_1ee1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x66];
    s16 m66;
    s32 m68;
};

s32 CharaDataRecFindSubRec_1ee1e0(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 l0;
    s32 t1;
    s16 t2;

    t0 = p0->m66;
    l0 = 0;
    while (l0 < t0) {
        t1 = p0->m68;
        t2 = *(s16 *)((u8 *)t1 + (((l0 * 0xC) + l0) << 3) + 0x8);
        if (p1 == t2) {
            return (t1 + (((l0 * 0xC) + l0) << 3));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
