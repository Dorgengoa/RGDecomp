/* rgp:protos */
#define RGP_SELF_InsectItemGetSatiety_386c30 1
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
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18];
    s8 m18;
};

s32 InsectItemGetSatiety_386c30(struct Obj0 *p0)
{
    return (s8)(p0->m18->m18);
}
