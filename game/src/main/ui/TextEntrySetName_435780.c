/* rgp:protos */
#define RGP_SELF_TextEntrySetName_435780 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s8 m00;
};

struct Obj1 {
    u8 m00;
};

void TextEntrySetName_435780(s32 p0, s32 p1)
{
    struct Obj1 *l0;
    struct Obj0 *l1;

    l0 = (struct Obj1 *)(p0 + 0x30);
    l1 = (struct Obj0 *)p1;
    while (l1->m00 != 0) {
        l0->m00 = l1->m00;
        l0 = (struct Obj1 *)((u8 *)l0 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 1);
    }
}
