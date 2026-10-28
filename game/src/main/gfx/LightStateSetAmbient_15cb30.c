/* rgp:protos */
#define RGP_SELF_LightStateSetAmbient_15cb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

extern struct Obj0 * D_004810A4;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x36B4];
    struct Obj2 *m36B4;
};

struct Obj1 {
    u128 m00;
};

struct Obj2 {
    u8 pad000[0x10];
    u128 m10;
};

void LightStateSetAmbient_15cb30(struct Obj1 *p0)
{
    if (D_004810A4->m36B4 != 0) {
        D_004810A4->m36B4->m10 = p0->m00;
    }
}
