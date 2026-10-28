/* rgp:protos */
#define RGP_SELF_EffHdlAssignIndex_1a6190 1
#include "port/game_protos.h"
#line 1
/* EffHdlAssignIndex_1a6190 -- shape-identical to merged EffHdlAssignIndex_1a41e0 (42 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     D_00481390 -> D_004813A0
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* lane N4 family: EffHdlAssignIndex_1a6190 / EffHdlAssignIndex_1a60e0 (168 B each).
   Substitution: the gp counter D_004813A0 -> D_0048139C. */

extern char D_0045A650[];
extern char D_0045A6B8[];
extern char D_0045A6D0[];
extern volatile u32 D_004813A0;

/*rgp*/

void EffHdlAssignIndex_1a6190(s16 *a0, u32 a1)
{
    s32 t;
    u32 c;
    u32 g;

    t = !(*(s32 *)a0 != 0);
    if (t == 0) {
        __assert(D_0045A650, 0x36, D_0045A6B8);
    }
    if (a1 > 0xFFFF) {
        __assert(D_0045A650, 0x37, D_0045A6D0);
    }
    c = D_004813A0 + 1;
    D_004813A0 = c;
    if (c > 0xFFFF) {
        D_004813A0 = 1;
    }
    g = D_004813A0;
    *a0 = a1;
    *(s16 *)((u8 *)a0 + 2) = g;
}
