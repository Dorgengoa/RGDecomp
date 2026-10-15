#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj5_FUN_001e73b0 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
    f32 m0C;         /* +0xC */
} Obj5_FUN_001e73b0;

extern s32 MapDataSetColorF_1e7360(f32, f32, f32, f32);

s32 MapDataSetColorVec_1e73b0(s32 a4, Obj5_FUN_001e73b0 *o)
{
    return MapDataSetColorF_1e7360(o->m00, o->m04, o->m08, o->m0C);
}
