#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecCopy_1cbe30(s32, void *);

s32 CharaGetPlacedPosMaybe_238280(void *p4, s32 a5)
{
    return VecCopy_1cbe30(a5, (u8 *)p4 + 0x100);
}
