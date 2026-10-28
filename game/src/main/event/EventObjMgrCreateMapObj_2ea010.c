/* rgp:protos */
#define RGP_SELF_EventObjMgrCreateMapObj_2ea010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002ea010 {
    u8 pad000[0x150];
    s32 m150;         /* +0x150 */
} Obj4_FUN_002ea010;

/*rgp*/

s32 EventObjMgrCreateMapObj_2ea010(Obj4_FUN_002ea010 *o, s32 a5, s32 a6, s32 a7)
{
    return ((s32)EvMapObjAddUnique_2ec150(a5, a6, a7, o->m150, (u8 *)o + 0xD0));
}
