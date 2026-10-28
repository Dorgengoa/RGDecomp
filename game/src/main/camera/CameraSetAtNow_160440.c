/* rgp:protos */
#define RGP_SELF_CameraSetAtNow_160440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u128 m00;
};

struct Obj1 {
    u8 pad000[0x50];
    u128 m50;
    u8 pad060[0x80];
    u128 mE0;
};

void CameraSetAtNow_160440(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->mE0 = p1->m00;
    p0->m50 = p1->m00;
}
