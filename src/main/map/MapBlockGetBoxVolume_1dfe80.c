#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 AreaBoxGetVolumeThunk_1e98b0(void *);

s32 MapBlockGetBoxVolume_1dfe80(void *p4)
{
    return AreaBoxGetVolumeThunk_1e98b0((u8 *)p4 + 0x74);
}
