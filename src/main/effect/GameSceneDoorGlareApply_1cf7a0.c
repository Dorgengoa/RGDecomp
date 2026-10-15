#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 DoorGlareParamsApplyIfActive_1ce730(void *, s32);

s32 GameSceneDoorGlareApply_1cf7a0(void *p4, s32 a5)
{
    return DoorGlareParamsApplyIfActive_1ce730((u8 *)p4 + 0x5934, a5);
}
