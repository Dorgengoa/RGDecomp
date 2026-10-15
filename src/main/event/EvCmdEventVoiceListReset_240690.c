#include "types.h"

extern s32 EventVoiceListReset_24e5e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EvCmdEventVoiceListReset_240690(s32 p0, s32 p1)
{
    s32 r;

    r = EventVoiceListReset_24e5e0((gEventContext->m04 + 0x420), p1);
    return 1;
}
