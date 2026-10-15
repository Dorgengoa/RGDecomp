#include "types.h"

/* Same shape as TextReaderSetKeywords_15f230, but BOTH calls take the same two arguments,
   so the register carried across the first call is p1, not p2. */

extern void CharaSetPosVec_2387e0(s32, s32);
extern void SrtSetPosFromVecThunk_1c7410(s32, s32);

void CharaSetPos_213a40(s32 p0, s32 p1)
{
    CharaSetPosVec_2387e0(p0, p1);
    SrtSetPosFromVecThunk_1c7410(p0, p1);
}
