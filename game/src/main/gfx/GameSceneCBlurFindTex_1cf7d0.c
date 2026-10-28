/* rgp:protos */
#define RGP_SELF_GameSceneCBlurFindTex_1cf7d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneCBlurFindTex_1cf7d0(void *p4)
{
    return ((s32)CBlurTexFindTex_1791a0((u8 *)p4 + 0x58C0));
}
