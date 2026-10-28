/* rgp:protos */
#define RGP_SELF_EventObjMgrCreateTargetPointObj_2ea110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002ea110 {
    u8 pad000[0x150];
    s32 m150;         /* +0x150 */
} Obj4_FUN_002ea110;

/*rgp*/

s32 EventObjMgrCreateTargetPointObj_2ea110(Obj4_FUN_002ea110 *o, s32 a5, s32 a6, s32 a7)
{
    return ((s32)EvTargetPointObjAddUnique_2eaf50(a5, a6, a7, o->m150, (u8 *)o + 0x130));
}
