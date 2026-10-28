/* rgp:protos */
#define RGP_SELF_ScreenFadeIn_1cf740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ScreenFadeIn_1cf740(void *p4, s32 a5)
{
    return (ScreenFadeBlockFadeIn_178310((u8 *)p4 + 0x5980, a5), (s32)0);
}
