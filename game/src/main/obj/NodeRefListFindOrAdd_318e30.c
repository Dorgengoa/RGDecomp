/* rgp:protos */
#define RGP_SELF_NodeRefListFindOrAdd_318e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x680];
    s16 m680;
};

s32 NodeRefListFindOrAdd_318e30(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s16 t0;
    s32 rv3;
    s32 r1;
    s32 rv2;
    s16 t1;
    s16 n;

    if (p1 == 0) {
        return -1;
    }
    r0 = NodeRefListFind_318ed0(p0, p1);
    if (r0 >= 0) {
        return r0;
    }
    t0 = p0->m680;
    if (t0 >= 0x10) {
        rv3 = -1;
    } else {
        r1 = NodeRefCopy_3191d0((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + ((t0 * 5) << 4)) + 0x180), p1);
        if (r1 == 0) {
            rv2 = -1;
        } else {
            t1 = p0->m680;
            n = t1 + 1;
            p0->m680 = n;
            rv2 = n - 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
