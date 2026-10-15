#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 DoorGlareParamsInit_1ce8a0(void *);

s32 GameSceneDoorGlareInit_1cf7c0(void *p4)
{
    return DoorGlareParamsInit_1ce8a0((u8 *)p4 + 0x5934);
}
