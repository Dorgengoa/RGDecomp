#include "types.h"

extern void EvObjReset_2f9eb0(void *);
extern void TargetRefClear_2e71d0(void *);
extern void EvSwitchRecInit_2f8840(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x158];
    u8 m158;
};

void EvSwitchObjReset_2f8670(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xE0));
    EvSwitchRecInit_2f8840((struct Obj0 *)((u8 *)p0 + 0x110));
    EvSwitchRecInit_2f8840((struct Obj0 *)((u8 *)p0 + 0x134));
    p0->m158 = 0;
}
