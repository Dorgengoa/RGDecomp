/* rgp:protos */
#define RGP_SELF_ScreenFadeOutColor_1cf730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ScreenFadeOutColor_1cf730(void *p4, s32 a5, f32 fa0, f32 fa1, f32 fa2)
{
    return (ScreenFadeBlockFadeOutColor_1782a0((u8 *)p4 + 0x5980, a5, fa0, fa1, fa2), (s32)0);
}
