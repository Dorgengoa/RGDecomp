#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 StateFlagTest_3ccd70(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 TopMenuRow6UnlockedMaybe_29ac20(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = GetGameData_1fede0();
    t0 = r0->m10;
    r1 = StateFlagTest_3ccd70(t0, 0x3E8);
    return (r1 & 0xFF);
}
