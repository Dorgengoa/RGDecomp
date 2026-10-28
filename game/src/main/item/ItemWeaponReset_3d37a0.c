/* rgp:protos */
#define RGP_SELF_ItemWeaponReset_3d37a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x16];
    u8 m16;
    u8 pad017[0x5];
    s8 m1C;
};

void ItemWeaponReset_3d37a0(struct Obj0 *p0)
{
    s32 l1;
    s32 l2;

    ItemReset_3d50d0(p0);
    p0->m16 = 0;
    l2 = 0;
    do {
        *(u8 *)((u8 *)p0 + l2 + 0x17) = 0;
        l1 = ((l2 + 1) < 5);
        l2 = (l2 + 1);
    } while (l1 != 0);
    p0->m1C = -1;
}
