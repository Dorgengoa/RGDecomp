#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004831D0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4EC];
    s16 m4EC;
};

void SaveSetPort_37b7c0(s32 p0)
{
    if (D_004831D0 != 0) {
        if (p0 >= 0) {
            if (p0 >= 0) {
                if (p0 < 2) {
                    D_004831D0->m4EC = p0;
                }
            }
        }
    }
}
