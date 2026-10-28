/* rgp:protos */
#define RGP_SELF_SoundSeqChanInit_1b5ef0 1
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
    u8 m01;
    u8 m02;
    u8 m03;
    u8 m04;
    u8 m05;
    u8 m06;
    u8 m07;
    u8 m08;
};

void SoundSeqChanInit_1b5ef0(struct Obj0 *p0)
{
    p0->m00 = 0x7F;
    p0->m01 = 0x7F;
    p0->m02 = 0;
    p0->m03 = 0x40;
    p0->m04 = 0;
    p0->m05 = 0x40;
    p0->m06 = 0;
    p0->m07 = 0;
    p0->m08 = 0;
}
