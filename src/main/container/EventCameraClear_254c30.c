#include "types.h"

extern void EventCameraReset_254a90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x48];
    u128 m50;
    u128 m60;
};

void EventCameraClear_254c30(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m50 = 0;
    p0->m60 = 0;
    EventCameraReset_254a90(p0);
}
