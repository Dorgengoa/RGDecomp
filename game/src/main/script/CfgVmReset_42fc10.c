/* rgp:protos */
#define RGP_SELF_CfgVmReset_42fc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x400];
    s32 m404;
    s32 m408;
    s32 m40C;
    s32 m410;
    s32 m414;
    s32 m418;
    s32 m41C;
    s32 m420;
    s32 m424;
    u8 pad428[0x400];
    u8 m828;
};

s32 CfgVmReset_42fc10(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m404 = 0;
    p0->m408 = 0;
    p0->m40C = 0;
    p0->m410 = 0;
    p0->m414 = 0;
    p0->m418 = 0;
    p0->m41C = 0;
    p0->m420 = 0;
    p0->m424 = 0;
    p0->m828 = 0;
    return 1;
}
