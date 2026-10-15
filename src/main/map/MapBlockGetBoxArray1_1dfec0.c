#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapBlockBoxListGetArray1_1e0390(void *);

s32 MapBlockGetBoxArray1_1dfec0(void *p4)
{
    return MapBlockBoxListGetArray1_1e0390((u8 *)p4 + 0x54);
}
