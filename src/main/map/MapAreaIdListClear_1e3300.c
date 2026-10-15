#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapIdListClearThunk_1e5ac0(void *);

s32 MapAreaIdListClear_1e3300(void *p4)
{
    return MapIdListClearThunk_1e5ac0((u8 *)p4 + 0x20B0);
}
