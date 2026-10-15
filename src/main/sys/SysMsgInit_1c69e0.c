#include "types.h"

extern s32 SysMsgClear_1c69d0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

struct Obj0 *SysMsgInit_1c69e0(struct Obj0 *p0)
{
    s32 r0;

    r0 = SysMsgClear_1c69d0();
    p0->m00 = 0;
    return p0;
}
