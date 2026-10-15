#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetShareCount_1dd560(void *);

s32 MapAreaGetShareCount_1dce50(void *p4)
{
    return MapRecTableGetShareCount_1dd560((u8 *)p4 + 0x54);
}
