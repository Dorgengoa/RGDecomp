#include "types.h"

extern void MatIdentity_1cbe40(void *);
extern void NavGraphStorageReset_311510(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    u8 mE0;
    u8 pad0E1[0x23];
    s32 m104;
    u8 pad108[0x4];
    s16 m10C;
    s16 m10E;
    u8 pad110[0x1];
    u8 m111;
    u8 pad112[0x1];
    u8 m113;
    s32 m114;
};

void NavGraphReset_3111a0(struct Obj0 *p0)
{
    MatIdentity_1cbe40(p0);
    MatIdentity_1cbe40((struct Obj0 *)((u8 *)p0 + 0x40));
    NavGraphStorageReset_311510((struct Obj0 *)((u8 *)p0 + 0x90));
    p0->mE0 = 0;
    p0->m10C = -1;
    p0->m10E = -1;
    p0->m113 = 0;
    p0->m111 = 0;
    p0->m114 = -1;
    p0->m104 = 0x442F0000;
}
