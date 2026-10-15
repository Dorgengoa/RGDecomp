#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj5_FUN_00304a80 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj5_FUN_00304a80;

extern s32 DoorCursorSetPosXyz_304a70(s32, f32, f32, f32);

s32 DoorCursorSetPos_304a80(s32 a4, Obj5_FUN_00304a80 *o)
{
    return DoorCursorSetPosXyz_304a70(a4, o->m00, o->m04, o->m08);
}
