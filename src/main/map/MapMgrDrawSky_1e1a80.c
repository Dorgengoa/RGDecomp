#include "types.h"

extern void MapSkyDraw_1e5fc0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
};

void MapMgrDrawSky_1e1a80(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m60;
    if ((t0 & 2) == 0) {
        MapSkyDraw_1e5fc0((struct Obj0 *)((u8 *)p0 + 0xE0));
    }
}
