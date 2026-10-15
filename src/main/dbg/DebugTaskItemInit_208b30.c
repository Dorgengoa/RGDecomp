#include "types.h"

extern void DebugMenuWidgetInit_2092c0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
};

void DebugTaskItemInit_208b30(struct Obj0 *p0)
{
    DebugMenuWidgetInit_2092c0(p0);
    p0->m30 = 0;
}
