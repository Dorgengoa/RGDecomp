/* rgp:protos */
#define RGP_SELF_UiEntryListResetEntryRect_28eb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    s16 m06;
    u8 pad008[0xC];
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
};

void UiEntryListResetEntryRect_28eb40(s32 p0, struct Obj0 *p1)
{
    if (p1 != 0) {
        p1->m16 = 0;
        p1->m14 = 0;
        p1->m1A = 0;
        p1->m18 = 0;
        p1->m1C = p1->m04;
        p1->m1E = p1->m06;
    }
}
