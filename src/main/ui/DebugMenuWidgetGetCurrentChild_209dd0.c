#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00209dd0 {
    u8 pad000[0x22];
    s16 m22;         /* +0x22 */
} Obj4_FUN_00209dd0;

extern s32 DebugMenuWidgetGetChild_209d90(void *, s32);

s32 DebugMenuWidgetGetCurrentChild_209dd0(Obj4_FUN_00209dd0 *o)
{
    return DebugMenuWidgetGetChild_209d90(o, o->m22);
}
