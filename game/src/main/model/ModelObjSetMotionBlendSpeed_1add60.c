/* rgp:protos */
#define RGP_SELF_ModelObjSetMotionBlendSpeed_1add60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ModelObjSetMotionBlendSpeed_1add60(void *p4, f32 fa0)
{
    return (MotionListSetBlendSpeedById_172170((u8 *)p4 + 0x1F0, -1, fa0), (s32)0);
}
