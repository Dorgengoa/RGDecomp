#include "types.h"

extern void MinimapMgrRelease_3220c0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x510];
    s32 m510;
    s32 m514;
    s32 m518;
    s32 m51C;
};

void MinimapMgrReset_322290(struct Obj0 *p0)
{
    MinimapMgrRelease_3220c0(p0, 0);
    p0->m510 = 0;
    p0->m514 = 0;
    p0->m518 = 0x3F800000;
    p0->m51C = 0;
}
