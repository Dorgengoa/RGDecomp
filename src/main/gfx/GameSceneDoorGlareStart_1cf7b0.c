#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 DoorGlareParamsStart_1ce7e0(void *);

s32 GameSceneDoorGlareStart_1cf7b0(void *p4)
{
    return DoorGlareParamsStart_1ce7e0((u8 *)p4 + 0x5934);
}
