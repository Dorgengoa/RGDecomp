/* rgp:protos */
#define RGP_SELF_ActCfgTableGetWalkMotionName_21f550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_0045D048[];

/*rgp*/

s32 ActCfgTableGetWalkMotionName_21f550(s32 a4, s32 a5, s32 a6)
{
    return ((s32)ActCfgTableGetInfoNameByMode_21f5b0(a4, a5, a6, 0x66, 0x70, 0x7A, 0x84, D_0045D048));
}
