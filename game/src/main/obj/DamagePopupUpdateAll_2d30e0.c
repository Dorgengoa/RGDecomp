/* rgp:protos */
#define RGP_SELF_DamagePopupUpdateAll_2d30e0 1
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

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x14];
    s32 m14;
};

struct Obj2 {
    u8 pad000[0x3C];
    u8 m3C;
};

void DamagePopupUpdateAll_2d30e0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 t1;
    struct Obj1 * t2;
    struct Obj2 *r1;
    s32 l0;
    u8 t3;
    struct Obj1 * t4;

    t0 = p0->m04;
    if (t0 != 0) {
        t1 = p0->m04->m14;
        l0 = 0;
        while (l0 < t1) {
            t2 = p0->m04;
            r1 = PoolGetUsedElem_36acb0(t2, l0);
            if (r1 != 0) {
                DamagePopupTick_2d39a0(r1);
                t3 = r1->m3C;
                if ((t3 & 1) == 0) {
                    t4 = p0->m04;
                    PoolFreeElemByPtr_36aa80(t4, r1);
                }
            }
            l0 = (l0 + 1);
        }
        return;
    }
}
