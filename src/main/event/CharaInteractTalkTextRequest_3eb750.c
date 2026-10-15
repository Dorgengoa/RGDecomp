#include "types.h"

extern void ActionPacketReset_3e3d00(void *);
extern void TalkTextRequestByKind_3e1b80(void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaInteractTalkTextRequest_3eb750(s32 p0)
{
    u128 v20[3];

    ActionPacketReset_3e3d00(v20);
    TalkTextRequestByKind_3e1b80(v20, (p0 + 0x34));
}
