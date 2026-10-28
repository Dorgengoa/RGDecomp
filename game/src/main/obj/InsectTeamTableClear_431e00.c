/* rgp:protos */
#define RGP_SELF_InsectTeamTableClear_431e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004840D8;
extern s32 D_004840DC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x1188];
    s32 m1188;
};

void InsectTeamTableClear_431e00(struct Obj0 *p0)
{
    D_004840D8 = 0;
    D_004840DC = 0;
    p0->m1188 = 0;
    InsectTeamTableReset_431d10(p0);
}
