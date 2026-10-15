#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_0045B070[];

extern s32 strcpy(void *, void *);

s32 XformRecSetDefaultNameMaybe_1c6940(void *p4)
{
    return strcpy((u8 *)p4 + 0x40, D_0045B070);
}
