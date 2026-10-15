#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002d2d90 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
} Obj4_FUN_002d2d90;

extern s32 PoolClear_36ade0(s32);

s32 DamagePopupListClearBufs_2d2d90(Obj4_FUN_002d2d90 *o)
{
    return PoolClear_36ade0(o->m04);
}
