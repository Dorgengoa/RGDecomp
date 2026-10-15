#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00213fc0 {
    u8 pad000[0x424];
    s16 m424;         /* +0x424 */
} Obj4_FUN_00213fc0;

extern s32 CharaTintUpdate_21ea90(void *, s32, f32);

s32 CharaUpdateTint_213fc0(Obj4_FUN_00213fc0 *o, f32 fa0)
{
    return CharaTintUpdate_21ea90((u8 *)o + 0x95C, o->m424, fa0);
}
