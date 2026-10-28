/* rgp:protos */
#define RGP_SELF_LoaderUnitReset_1ce370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
    u8 pad001[0x7F];
    s16 m80;
    s16 m82;
    s16 m84;
    s16 m86;
    s32 m88;
    s32 m8C;
    s32 m90;
    s32 m94;
};

void LoaderUnitReset_1ce370(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m80 = -1;
    p0->m84 = 0;
    p0->m82 = 0;
    p0->m86 = 0;
    p0->m88 = 0;
    p0->m8C = 0;
    p0->m90 = 0;
    p0->m94 = 0;
}
