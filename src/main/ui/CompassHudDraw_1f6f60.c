#include "types.h"

extern void * GetGameData_1fede0(void);
extern void CompassHudRender_370fb0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B8800[];

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj2 *m0C;
    u8 pad010[0x8];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x1A4];
    u8 m1A4;
};

struct Obj2 {
    u8 pad000[0x2A];
    s16 m2A;
};

void CompassHudDraw_1f6f60(void)
{
    struct Obj0 *r0;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    if ((r0->m18->m1A4 & 1) == 0) {
        if (r0->m0C->m2A != 0) {
            CompassHudRender_370fb0(D_004B8800);
        }
    }
}
