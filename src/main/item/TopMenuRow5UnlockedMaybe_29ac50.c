#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 TopMenuRow5UnlockedMaybe_29ac50(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = GetGameData_1fede0();
    t0 = r0->m18;
    r1 = InvHasItemInCategory_3c7f40(t0, 0x40E5, 0xA, 0);
    return (r1 & 0xFF);
}
