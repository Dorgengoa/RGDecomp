#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GameSceneSoundSlotStartFromData_1d0bc0(s32, s32, s32);

s32 GameSceneSoundSlot6StartFromData_1d06e0(s32 a4, s32 a5)
{
    return GameSceneSoundSlotStartFromData_1d0bc0(a4, 6, a5);
}
