/* rgp:protos */
#define RGP_SELF_MotionEventCfgEndCmd_1b4450 1
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
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x3C];
    s32 m3C;
};

s32 MotionEventCfgEndCmd_1b4450(s32 p0, s32 p1, struct Obj0 *p2)
{
    p2->m00->m3C = 0;
    return 1;
}
