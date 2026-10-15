#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapCaptionShow_33f940(void *);

s32 MapMgrCaptionShow_1e2650(void *p4)
{
    return MapCaptionShow_33f940((u8 *)p4 + 0x18E8);
}
