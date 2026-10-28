/* rgp:protos */
#define RGP_SELF_DataTableClearHook_422ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x98];
    s32 m98;
    s32 m9C;
    s32 mA0;
    s32 mA4;
    s32 mA8;
    s32 mAC;
    s32 mB0;
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    s32 mC4;
    s32 mC8;
    s32 mCC;
};

void DataTableClearHook_422ae0(struct Obj0 *p0)
{
    p0->m98 = 0;
    p0->mA4 = 0;
    p0->mA8 = 0;
    p0->m9C = 0;
    p0->mAC = 0;
    p0->mB0 = 0;
    p0->mA0 = 0;
    p0->mB4 = 0;
    p0->mB8 = 0;
    p0->mC0 = 0;
    p0->mBC = 0;
    p0->mC0 = 0;
    p0->mC4 = 0;
    p0->mC8 = 0;
    p0->mCC = 0;
}
