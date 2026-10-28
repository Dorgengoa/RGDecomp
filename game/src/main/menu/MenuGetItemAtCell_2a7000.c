/* rgp:protos */
#define RGP_SELF_MenuGetItemAtCell_2a7000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482374;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

s32 MenuGetItemAtCell_2a7000(s32 p0, struct Obj0 *p1)
{
    struct Obj1 *r0;
    s32 t0;
    s32 r1;
    s32 rv2;
    s32 t3;
    s32 rv3;
    s32 t4;
    s32 r4;
    s32 t5;
    s32 r5;

    r0 = GetGameData_1fede0();
    t0 = D_00482374;
    r1 = MenuGetMode_2a4e30(t0);
    rv2 = p0;
    if (r1 == 9) {
        rv2 = 0;
    }
    rv3 = p1->m12;
    t3 = p1->m10;
    t4 = D_00482374;
    r4 = MenuGetMode_2a4e30(t4);
    t5 = r0->m18;
    r5 = ((s32)InvFindByCategoryIndex_3c86e0(t5, r4, rv2, t3, rv3, 0));
    return r5;
}
