#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockReset_178470(void *);

s32 ScreenFadeReset_1cf760(void *p4)
{
    return ScreenFadeBlockReset_178470((u8 *)p4 + 0x5980);
}
