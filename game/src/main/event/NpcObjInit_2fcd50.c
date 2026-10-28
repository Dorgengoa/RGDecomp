/* rgp:protos */
#define RGP_SELF_NpcObjInit_2fcd50 1
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
    s16 m00;
    u8 pad002[0xC2];
    s16 mC4;
    s16 mC6;
    s16 mC8;
    s16 mCA;
    s16 mCC;
    s16 mCE;
    u8 mD0;
    u8 mD1;
    u8 pad0D2[0x2];
    s32 mD4;
    u8 pad0D8[0x4];
    s32 mDC;
};

void NpcObjInit_2fcd50(struct Obj0 *p0)
{
    p0->mC6 = 0;
    p0->mC4 = -1;
    p0->mC8 = -1;
    p0->m00 = 0;
    p0->mD4 = 0;
    p0->mCC = -1;
    p0->mCE = 0;
    p0->mDC = 0;
    p0->mD0 = 0;
    p0->mD1 = 0;
    p0->mCA = 0;
    HeadLookInit_1c5c50((struct Obj0 *)((u8 *)p0 + 0x10));
}
