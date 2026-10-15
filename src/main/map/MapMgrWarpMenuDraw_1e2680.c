#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 WarpMenuDrawIconsMaybe_39d400(void *);

s32 MapMgrWarpMenuDraw_1e2680(void *p4)
{
    return WarpMenuDrawIconsMaybe_39d400((u8 *)p4 + 0x18B0);
}
