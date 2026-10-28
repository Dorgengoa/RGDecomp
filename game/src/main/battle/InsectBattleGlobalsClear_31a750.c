/* rgp:protos */
#define RGP_SELF_InsectBattleGlobalsClear_31a750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F230;
extern s32 D_00482AF0;
extern s32 D_00482AF4;
extern s32 D_00482AF8;
extern u8 D_004E7FB0[];

void InsectBattleGlobalsClear_31a750(void)
{
    MemStackClear_14dff0(D_004E7FB0);
    D_00482AF0 = 0;
    D_0047F230 = -1;
    D_00482AF4 = 0;
    D_00482AF8 = 0;
}
