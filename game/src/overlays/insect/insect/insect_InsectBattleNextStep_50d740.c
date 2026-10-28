/* rgp:protos */
#define RGP_SELF_insect_InsectBattleNextStep_50d740 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050D740 -- 16 B / 4 words.  `daddu $6,$5,$0 / addiu $7,$0,0x1 /
 * j insect_InsectBattleSetStep_50d7a0 / daddu $5,$0,$0`: a TAIL CALL that re-shuffles two
 * incoming arguments into a four-argument callee -- the wrapper's own second
 * parameter becomes arg THREE, with 0 and 1 as the constant arg two and four.
 *
 * $6 has to be set before $5 is clobbered, which is why retail issues the
 * moves in 6, 7, 5 order; that falls out of the call, it is not a source order.
 * The prototype is the settled one (insect_InsectBattleObjInit_50e810.c and ~40 others):
 *   extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
 */

typedef struct Ins { u8 raw[1]; } Ins;

/*rgp*/

void insect_InsectBattleNextStep_50d740(Ins *o, s32 k)
{
    insect_InsectBattleSetStep_50d7a0(o, 0, k, 1);
}
