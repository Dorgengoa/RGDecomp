#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj5_FUN_001e9220 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj5_FUN_001e9220;

extern s32 MapLinkSetPosXyz_1e9210(s32, f32, f32, f32);

s32 MapLinkSetPos_1e9220(s32 a4, Obj5_FUN_001e9220 *o)
{
    return MapLinkSetPosXyz_1e9210(a4, o->m00, o->m04, o->m08);
}
