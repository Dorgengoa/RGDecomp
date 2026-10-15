#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00238540 {
    u8 pad000[0x404];
    s32 m404;         /* +0x404 */
} Obj4_FUN_00238540;

extern s32 StrEqualNonNull_1ca6c0(s32, s32);

s32 CharaIsCurMotion_238540(Obj4_FUN_00238540 *o, s32 a5)
{
    return StrEqualNonNull_1ca6c0(o->m404, a5);
}
