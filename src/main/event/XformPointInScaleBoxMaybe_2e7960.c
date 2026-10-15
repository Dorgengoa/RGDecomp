#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002e7960 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj4_FUN_002e7960;

extern s32 XformPointInBoxSym_2e7950(f32, f32, f32);

s32 XformPointInScaleBoxMaybe_2e7960(Obj4_FUN_002e7960 *o)
{
    return XformPointInBoxSym_2e7950(o->m08, o->m00, o->m04);
}
