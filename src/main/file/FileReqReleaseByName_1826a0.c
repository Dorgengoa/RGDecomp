#include "types.h"

extern s32 Strcasecmp_1345b8(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00495FD0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x120];
    s32 m120;
};

void FileReqReleaseByName_1826a0(s32 p0)
{
    s32 l1;
    struct Obj0 *l0;
    s32 t0;
    s32 r2;

    l1 = 0;
    l0 = (struct Obj0 *)D_00495FD0;
    while (l1 < 0x20) {
        t0 = l0->m120;
        if (t0 != 0) {
            r2 = Strcasecmp_1345b8(p0, (struct Obj0 *)((u8 *)l0 + 0x8C));
            if (r2 == 0) {
                l0->m120 = 0;
                return;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj0 *)((u8 *)l0 + 0x128);
    }
}
