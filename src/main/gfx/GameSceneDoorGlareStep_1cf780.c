#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 DoorGlareParamsStep_1ce760(void *);

s32 GameSceneDoorGlareStep_1cf780(void *p4)
{
    return DoorGlareParamsStep_1ce760((u8 *)p4 + 0x5934);
}
