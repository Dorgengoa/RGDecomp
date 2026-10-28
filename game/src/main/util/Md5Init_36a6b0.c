/* rgp:protos */
#define RGP_SELF_Md5Init_36a6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s64 m00;
    s64 m08;
    s64 m10;
    s64 m18;
    s64 m20;
    s64 m28;
};

void Md5Init_36a6b0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m08 = 0;
    p0->m10 = 0x67452301;
    p0->m18 = ((((s64)0xEFCD) << 0x10) | 0xAB89);
    p0->m20 = ((((s64)0x98BA) << 0x10) | 0xDCFE);
    p0->m28 = 0x10325476;
}
