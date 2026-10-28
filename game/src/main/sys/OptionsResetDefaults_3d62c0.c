/* rgp:protos */
#define RGP_SELF_OptionsResetDefaults_3d62c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s64 m08;
    s16 m10;
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
    s16 m20;
    s16 m22;
    s16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
    s16 m2C;
    s16 m2E;
};

void OptionsResetDefaults_3d62c0(struct Obj0 *p0)
{
    p0->m08 = 0;
    p0->m10 = 0;
    p0->m12 = 0;
    p0->m14 = 0xA;
    p0->m16 = 0xA;
    p0->m18 = 0xA;
    p0->m1A = 1;
    p0->m1C = 1;
    p0->m1E = 1;
    p0->m20 = 1;
    p0->m22 = 1;
    p0->m26 = 1;
    p0->m28 = 1;
    p0->m2A = 1;
    p0->m2C = 1;
    p0->m24 = 0;
    p0->m2E = 0;
}
