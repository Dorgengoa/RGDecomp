#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_func_003147A0 {
    s32 m000;         /* +0x00 */
} Obj4_func_003147A0;

extern s32 HandleRegistryDrawAll_314b70(s32, s32, s32, s32);

s32 HandleRegistryRefDrawAll_3147a0(Obj4_func_003147A0 *o, s32 a5, s32 a6, s32 a7)
{
    return HandleRegistryDrawAll_314b70(o->m000, a5, a6, a7);
}
