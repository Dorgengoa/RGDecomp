#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GameSceneSoundSlotFree_1d1210(s32, s32);

s32 GameSceneSoundSlot6Free_1d0850(s32 a4)
{
    return GameSceneSoundSlotFree_1d1210(a4, 6);
}
