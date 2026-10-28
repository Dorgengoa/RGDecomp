/* rgp:protos */
#define RGP_SELF_CharaSysStateFlag24Bit0Related_3a38c0 1
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
    u8 pad000[0x238];
    struct Obj1 *m238;
};

struct Obj1 {
    u8 pad000[0x24];
    u8 m24;
};

s32 CharaSysStateFlag24Bit0Related_3a38c0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    u8 t1;

    t0 = p0->m238;
    if (t0 != 0) {
        t1 = p0->m238->m24;
        return (t1 & 1);
    }
    return 0;
}
