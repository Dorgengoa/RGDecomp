#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MotionListSetRateById_172110(void *, s32, s32, f32);

s32 ModelObjSetMotionRate_1add50(void *p4, s32 a5, f32 fa0)
{
    return MotionListSetRateById_172110((u8 *)p4 + 0x1F0, -1, a5, fa0);
}
