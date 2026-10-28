/* rgp:protos */
#define RGP_SELF_CameraRecSwapByte10Maybe_142dc0 1
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
    u8 pad000[0xF20];
    struct Obj1 *mF20;
};

struct Obj1 {
    u8 pad000[0x10];
    u8 m10;
};

u8 CameraRecSwapByte10Maybe_142dc0(struct Obj0 *p0, s32 p1)
{
    u8 old0;

    old0 = p0->mF20->m10;
    p0->mF20->m10 = p1;
    return old0;
}
