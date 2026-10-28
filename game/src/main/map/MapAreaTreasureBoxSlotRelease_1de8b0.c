/* rgp:protos */
#define RGP_SELF_MapAreaTreasureBoxSlotRelease_1de8b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

void MapAreaTreasureBoxSlotRelease_1de8b0(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;

    r0 = GetDrawCtxNameTable_15de40();
    t0 = p0->m08;
    NameTableFreeGroup_158ac0(r0, t0);
    MapAreaTreasureBoxSlotReset_1de8f0(p0);
}
