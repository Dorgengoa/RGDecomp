#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00314790 {
    s32 m000;         /* +0x00 */
} Obj4_FUN_00314790;

extern s32 HandleRegistryReleaseAll_314ac0(s32, s32, s32, s32);

s32 HandleRegistryClear_314790(Obj4_FUN_00314790 *o, s32 a5, s32 a6, s32 a7)
{
    return HandleRegistryReleaseAll_314ac0(o->m000, a5, a6, a7);
}
