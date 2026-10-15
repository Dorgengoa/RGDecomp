#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapSkySetHeap_1e6320(void *, s32);

s32 MapMgrSetSkyHeap_1e3400(void *p4, s32 a5)
{
    return MapSkySetHeap_1e6320((u8 *)p4 + 0xE0, a5);
}
