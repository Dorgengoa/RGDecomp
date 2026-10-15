#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MotionListSetBlendSpeedById_172170(void *, s32, f32);

s32 ModelObjSetMotionBlendSpeed_1add60(void *p4, f32 fa0)
{
    return MotionListSetBlendSpeedById_172170((u8 *)p4 + 0x1F0, -1, fa0);
}
