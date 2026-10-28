/* rgp:protos */
#define RGP_SELF_BattleHistoryReset_3a7f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x2];
    s64 m08;
    s64 m10;
};

s32 BattleHistoryReset_3a7f30(struct Obj0 *p0)
{
    s32 l1;

    p0->m00 = 0;
    p0->m02 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m10 = 0;
    BattleRecordStatsReset_3a7fb0((struct Obj0 *)((u8 *)p0 + 0x18));
    l1 = 0;
    do {
        BattleRecordReset_3a7fd0((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l1 * 0x60)) + 0x30));
        l1 = (l1 + 1);
    } while (l1 < 5);
    return 1;
}
