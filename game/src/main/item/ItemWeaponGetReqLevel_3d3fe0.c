/* rgp:protos */
#define RGP_SELF_ItemWeaponGetReqLevel_3d3fe0 1
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
    u8 pad000[0x4];
    u8 m04;
};

s32 ItemWeaponGetReqLevel_3d3fe0(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    u8 t1;

    t0 = p0->m10;
    r0 = ItemDefGetWeaponData_40e110(t0);
    if (r0 != 0) {
        t1 = r0->m04;
        return (t1 & 0x7F);
    }
    return 0;
}
