/* rgp:protos */
#define RGP_SELF_EventObjSetScale_2e72e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj5_FUN_002e72e0 {
    f32 m00;         /* +0x0 */
    f32 m04;         /* +0x4 */
    f32 m08;         /* +0x8 */
} Obj5_FUN_002e72e0;

/*rgp*/

s32 EventObjSetScale_2e72e0(s32 a4, Obj5_FUN_002e72e0 *o)
{
    return (EventObjSetScaleXyz_2e72d0(a4, o->m00, o->m04, o->m08), (s32)0);
}
