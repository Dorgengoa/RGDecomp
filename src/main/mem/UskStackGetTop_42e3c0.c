#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_0042e3c0 {
    u8 pad000[0x20];
    s32 m20;         /* +0x20 */
    u8 pad024[0x4];
    s32 m28;         /* +0x28 */
} Obj4_FUN_0042e3c0;

extern s32 PtrAdd_42e4d0(s32, s32);

s32 UskStackGetTop_42e3c0(Obj4_FUN_0042e3c0 *o)
{
    return PtrAdd_42e4d0(o->m20, o->m28);
}
