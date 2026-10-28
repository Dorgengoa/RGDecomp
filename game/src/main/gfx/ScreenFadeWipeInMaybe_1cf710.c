/* rgp:protos */
#define RGP_SELF_ScreenFadeWipeInMaybe_1cf710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ScreenFadeWipeInMaybe_1cf710(void *p4, s32 a5, s32 a6, f32 fa0)
{
    return (ScreenFadeBlockWipeInMaybe_1781a0((u8 *)p4 + 0x5980, a5, a6, fa0), (s32)0);
}
