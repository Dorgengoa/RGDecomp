#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CBlurTexFindTex_1791a0(void *);

s32 GameSceneCBlurFindTex_1cf7d0(void *p4)
{
    return CBlurTexFindTex_1791a0((u8 *)p4 + 0x58C0);
}
