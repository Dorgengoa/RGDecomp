#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetBoxes_1dd570(void *);

s32 MapAreaGetBoxes_1dcde0(void *p4)
{
    return MapRecTableGetBoxes_1dd570((u8 *)p4 + 0x54);
}
