#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x170];
    s32 m170;
    s32 m174;
};

s32 MinimapGetEntryBlockName_324a40(struct Obj0 *p0)
{
    s32 t0;
    s32 rv0;
    s32 t1;

    t0 = p0->m174;
    rv0 = t0;
    if (t0 == 0) {
        t1 = p0->m170;
        rv0 = t1;
    }
    if (rv0 == 0) {
        return 0;
    }
    return (rv0 + 0x34);
}
