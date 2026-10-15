#include "types.h"

extern void TargetRefClear_2e71d0(void *);
extern void TargetSlotReset_3211c0(void *);
extern void TargetMngResetAim_31ed70(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void TargetMngInit_320910(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m08 = 0;
    p0->m04 = 0;
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xC0));
    p0->m0C = 0;
    TargetSlotReset_3211c0((struct Obj0 *)((u8 *)p0 + 0x10));
    TargetMngResetAim_31ed70(p0);
}
