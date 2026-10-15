#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 EventVoiceListInit_24f580(void *, s32);

s32 EventPlayerInitVoiceList_249b50(void *p4, s32 a5)
{
    return EventVoiceListInit_24f580((u8 *)p4 + 0x420, a5);
}
