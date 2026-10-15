#include "types.h"

extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 InsectCageMenuSlotConfirm_390340(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m10;
    if (t0 >= 0) {
        InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
        InsectCageMenuSelectEntry_390d40(0x7532, 1);
    }
    return 1;
}
