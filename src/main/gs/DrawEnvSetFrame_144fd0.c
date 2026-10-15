#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00144fd0 {
    u8 pad000[0x270];
    s32 m270;         /* +0x270 */
} Obj4_FUN_00144fd0;

extern s32 DrawEnvSetFrame_1575e0(s32, s32, s32, s32);

s32 DrawEnvSetFrame_144fd0(Obj4_FUN_00144fd0 *o, s32 a5, s32 a6, s32 a7)
{
    return DrawEnvSetFrame_1575e0(o->m270, a5, a6, a7);
}
