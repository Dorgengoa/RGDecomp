/* rgp:protos */
#define RGP_SELF_BattleRecordStatsReset_3a7fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003a7fb0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 pad008[0x2];
    s16 m0A;         /* +0xA */
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
} Obj_FUN_003a7fb0;

void BattleRecordStatsReset_3a7fb0(Obj_FUN_003a7fb0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m0A = 0;
    o->m0C = 0;
    o->m10 = 0;
}
