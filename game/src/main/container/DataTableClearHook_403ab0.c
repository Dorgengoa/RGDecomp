/* rgp:protos */
#define RGP_SELF_DataTableClearHook_403ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x94];
    s32 m94;
    s32 m98;
    s32 m9C;
    s16 mA0;
    u8 pad0A2[0x2];
    s32 mA4;
};

void DataTableClearHook_403ab0(struct Obj0 *p0)
{
    p0->m98 = 0;
    p0->m9C = 0;
    p0->m94 = 0;
    p0->mA0 = 0;
    p0->mA4 = 0;
}
