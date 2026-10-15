#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GameSceneSoundSlotRequestLoad_1d0b20(s32, s32, s32, s32);

s32 GameSceneSoundSlot0RequestLoad_1d06c0(s32 a4, s32 a5)
{
    return GameSceneSoundSlotRequestLoad_1d0b20(a4, 0, 0, a5);
}
