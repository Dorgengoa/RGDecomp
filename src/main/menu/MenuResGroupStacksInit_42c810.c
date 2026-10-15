#include "types.h"

extern void ResGroupClearAll_42c8f0(s32);
extern s32 ResGroupStackInit_42c600(s32, s32, s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00468720[];
extern u8 D_00468730[];
extern u8 D_00468740[];
extern u8 D_00468750[];

s32 MenuResGroupStacksInit_42c810(s32 p0, s32 p1)
{
    s32 r1;
    s32 rv7;
    s32 r2;
    s32 rv6;
    s32 r3;
    s32 rv5;
    s32 r4;

    ResGroupClearAll_42c8f0(p0);
    r1 = ResGroupStackInit_42c600(p0, p1, 0, D_00468720, 0x1600);
    rv7 = rv6;
    if ((r1 & 0xFF) == 0) {
        rv7 = 0;
    } else {
        r2 = ResGroupStackInit_42c600(p0, 0, 1, D_00468730, 0);
        rv6 = rv5;
        if ((r2 & 0xFF) == 0) {
            rv6 = 0;
        } else {
            r3 = ResGroupStackInit_42c600(p0, 0, 2, D_00468740, 0);
            rv5 = (r4 & 0xFF);
            if ((r3 & 0xFF) == 0) {
                rv5 = 0;
            } else {
                r4 = ResGroupStackInit_42c600(p0, 0, 3, D_00468750, 0);
                rv5 = (r4 & 0xFF);
            }
            rv6 = rv5;
        }
        rv7 = rv6;
    }
    return rv7;
}
