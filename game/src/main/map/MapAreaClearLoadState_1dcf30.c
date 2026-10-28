/* rgp:protos */
#define RGP_SELF_MapAreaClearLoadState_1dcf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE6];
    s16 mE6;
    u8 pad0E8[0xE0];
    s16 m1C8;
    s16 m1CA;
};

void MapAreaClearLoadState_1dcf30(struct Obj0 *p0)
{
    s32 l1;

    MapDataClearLoadState_1e7c30(p0);
    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x128) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x178) = 0;
        l1 = (l1 + 1);
    } while (l1 < 0x14);
    p0->m1C8 = 0;
    p0->m1CA = 0;
    p0->mE6 = -1;
}
