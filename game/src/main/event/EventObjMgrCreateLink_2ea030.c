/* rgp:protos */
#define RGP_SELF_EventObjMgrCreateLink_2ea030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002ea030 {
    u8 pad000[0x150];
    s32 m150;         /* +0x150 */
} Obj4_FUN_002ea030;

/*rgp*/

s32 EventObjMgrCreateLink_2ea030(Obj4_FUN_002ea030 *o, s32 a5, s32 a6, s32 a7)
{
    return ((s32)EvObjLinkAddUnique_2ebf10(a5, a6, a7, o->m150, (u8 *)o + 0xC0));
}
