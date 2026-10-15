#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002e7750 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj4_FUN_002e7750;

extern s32 XformGetScaledMatrix_2e76b0(void *, s32, f32, f32, f32);

s32 XformGetMatrix_2e7750(Obj4_FUN_002e7750 *o, s32 a5)
{
    return XformGetScaledMatrix_2e76b0(o, a5, o->m00, o->m04, o->m08);
}
