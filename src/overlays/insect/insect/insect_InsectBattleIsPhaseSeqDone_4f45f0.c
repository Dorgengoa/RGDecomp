#include "types.h"
/* insect 0x004F45F0 -- pass-28 unnamed-listing conversion.  `not` + `sltiu 1`
 * with NO trailing `andi 0xFF` is an s32 0/1 predicate return, and the `not`
 * (rather than a materialised -1 and an `xor`) is what says the source
 * complements the loaded halfword before testing it. */
typedef struct Obj {
    u8 pad0000[0x5DD0];
    s16 m5DD0;         /* +0x5DD0 */
} Obj;

s32 insect_InsectBattleIsPhaseSeqDone_4f45f0(Obj *o)
{
    return (~o->m5DD0) == 0;
}
