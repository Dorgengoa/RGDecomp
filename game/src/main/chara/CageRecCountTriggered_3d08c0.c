/* rgp:protos */
#define RGP_SELF_CageRecCountTriggered_3d08c0 1
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
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0xA];
    s16 m0A;
};

struct Obj2 {
    u8 pad000[0xE];
    u8 m0E;
};

s32 CageRecCountTriggered_3d08c0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 l1;
    s32 l0;
    struct Obj2 *r2;
    struct Obj2 * rv5;
    s32 rv6;
    u8 t2;
    u8 rv3;
    s32 rv4;

    t0 = p0->m18;
    t1 = p0->m18->m0A;
    l0 = 0;
    l1 = 0;
    while (l0 < t1) {
        r2 = CageRecGetEntry_3d0880(p0, l0);
        rv5 = (struct Obj2 *)r2;
        rv6 = l1;
        if (r2 != 0) {
            t2 = r2->m0E;
            rv3 = 0;
            rv4 = l1;
            if ((t2 & 1) != 0) {
                rv3 = (t2 & 1);
                rv4 = (l1 + 1);
            }
            rv5 = (struct Obj2 *)rv3;
            rv6 = rv4;
        }
        l0 = (l0 + 1);
        l1 = rv6;
    }
    return l1;
}
