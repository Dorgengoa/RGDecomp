/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityPageSetRowRange_341ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482364;
extern struct Obj0 * D_00482378;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x74];
    s16 m74;
};

struct Obj1 {
    u8 pad000[0xE];
    s16 m0E;
    u8 pad010[0x2];
    s16 m12;
};

struct Obj1 *MenuCharaAbilityPageSetRowRange_341ba0(void)
{
    s32 t0;
    struct Obj1 *r0;
    struct Obj0 * t1;
    s16 t2;
    struct Obj0 * t3;
    s16 t4;

    t0 = D_00482364;
    r0 = UiEntryListFindByTag_28ea40(t0, 0x19);
    t1 = D_00482378;
    t2 = D_00482378->m74;
    if ((t2 < 7) != 0) {
        r0->m0E = (t2 + -1);
    } else {
        r0->m0E = 5;
    }
    t3 = D_00482378;
    t4 = D_00482378->m74;
    r0->m12 = (t4 + -1);
    return r0;
}
