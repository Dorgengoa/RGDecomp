/* rgp:protos */
#define RGP_SELF_DataTableClearHook_4247a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483F0C;
extern s32 D_00483F10;
extern u8 D_00483F14;

struct Obj0;

struct Obj0 {
    u8 pad000[0x94];
    s16 m94;
    u8 pad096[0x2];
    s32 m98;
};

void DataTableClearHook_4247a0(struct Obj0 *p0)
{
    p0->m94 = 0;
    p0->m98 = 0;
    D_00483F0C = 0;
    D_00483F10 = 0;
    D_00483F14 = 0;
}
