#include "types.h"
/* insect 0x512E10 -- 8 B / 2 words.  `j insect_InsectPieceTestStatus_513280` with
 * `addiu $5, $0, 0x11` in the delay slot: a TAIL CALL, so the wrapper's return
 * type has to agree with the callee's (s32, settled in insect_InsectBattleMenuFirstTurnSelect_4fb1a0.c). */

extern s32 insect_InsectPieceTestStatus_513280(void *e, s32 k);

s32 insect_InsectPieceHasLandedHitMaybe_512e10(void *e)
{
    return insect_InsectPieceTestStatus_513280(e, 0x11);
}
