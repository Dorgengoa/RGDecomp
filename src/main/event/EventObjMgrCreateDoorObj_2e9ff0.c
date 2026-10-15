#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002e9ff0 {
    u8 pad000[0x150];
    s32 m150;         /* +0x150 */
} Obj4_FUN_002e9ff0;

extern s32 EvDoorObjAddUnique_2ec390(s32, s32, s32, s32, void *);

s32 EventObjMgrCreateDoorObj_2e9ff0(Obj4_FUN_002e9ff0 *o, s32 a5, s32 a6, s32 a7)
{
    return EvDoorObjAddUnique_2ec390(a5, a6, a7, o->m150, (u8 *)o + 0xE0);
}
