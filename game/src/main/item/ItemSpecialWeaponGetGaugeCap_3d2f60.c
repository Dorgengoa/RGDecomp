/* rgp:protos */
#define RGP_SELF_ItemSpecialWeaponGetGaugeCap_3d2f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj1 {
    u8 pad000[0x2C];
    s8 m2C;
};

s32 ItemSpecialWeaponGetGaugeCap_3d2f60(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    s8 t1;

    t0 = p0->m10;
    r0 = ItemDefGetSpecialWeaponData_40e0e0(t0);
    if (r0 != 0) {
        t1 = r0->m2C;
        return t1;
    }
    return 0;
}
