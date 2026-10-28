/* rgp:protos */
#define RGP_SELF_VoBufGetData_1d49c0 1
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
    s32 m00;
    u8 pad004[0x8];
    s32 m0C;
};

s32 VoBufGetData_1d49c0(struct Obj0 *p0)
{
    s32 r0;
    s32 rv1;
    s32 t0;
    s32 t1;

    r0 = ((unsigned char)VoBufIsFull_1d4a90(p0));
    rv1 = (t1 + (((t0 << 3) - t0) << 0x11));
    if (r0 != 0) {
        rv1 = 0;
    } else {
        t0 = p0->m0C;
        t1 = p0->m00;
        rv1 = (t1 + (((t0 << 3) - t0) << 0x11));
    }
    return rv1;
}
