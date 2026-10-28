/* rgp:protos */
#define RGP_SELF_SaveIconFilesSetAll_375b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
    u8 pad064[0x8];
    s32 m6C;
};

void SaveIconFilesSetAll_375b10(s32 p0, struct Obj0 *p1)
{
    s32 l0;
    s32 l1;
    s32 t0;
    s32 t1;

    if (p1 != 0) {
        l1 = 0;
        do {
            strcpy((p0 + (l1 << 5)), p1);
            t0 = p1->m60;
            *(s32 *)((u8 *)p0 + (l1 << 2) + 0x60) = t0;
            t1 = p1->m6C;
            *(s32 *)((u8 *)p0 + (l1 << 2) + 0x6C) = t1;
            l0 = ((l1 + 1) < 3);
            l1 = (l1 + 1);
        } while (l0 != 0);
        return;
    }
}
