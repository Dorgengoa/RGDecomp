#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapCaptionUpdate_33f580(void *);

s32 MapMgrCaptionUpdate_1e2630(void *p4)
{
    return MapCaptionUpdate_33f580((u8 *)p4 + 0x18E8);
}
