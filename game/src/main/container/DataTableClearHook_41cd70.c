/* rgp:protos */
#define RGP_SELF_DataTableClearHook_41cd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483E44;

struct Obj0;

struct Obj0 {
    u8 pad000[0x94];
    s32 m94;
};

void DataTableClearHook_41cd70(struct Obj0 *p0)
{
    D_00483E44 = 0;
    p0->m94 = 0;
}
