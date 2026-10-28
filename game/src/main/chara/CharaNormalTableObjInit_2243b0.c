/* rgp:protos */
#define RGP_SELF_CharaNormalTableObjInit_2243b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s64 m10;
    s64 m18;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s16 m30;
    s16 m32;
    s16 m34;
    s16 m36;
    s32 m38;
    s16 m3C;
    s16 m3E;
};

void CharaNormalTableObjInit_2243b0(struct Obj0 *p0)
{
    DListNodeInit_42ec10(p0);
    p0->m20 = 0;
    p0->m36 = 0;
    p0->m10 = 0;
    p0->m18 = 0;
    p0->m24 = 0;
    p0->m30 = 0;
    p0->m28 = 0;
    p0->m32 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m3E = -1;
    p0->m38 = 0;
    p0->m3C = 0;
}
