/* rgp:protos */
#define RGP_SELF_PauseSysInit_2f65a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047EF70;
extern s32 D_0047EF74;
extern s32 D_0047EF78;
extern s32 D_00482768;
extern s32 D_0048276C;
extern s32 D_00482770;
extern u8 D_00482774;
extern u8 D_00482778;

void PauseSysInit_2f65a0(void)
{
    D_00482774 = 1;
    D_0048276C = 0;
    D_00482768 = -1;
    D_00482770 = 0;
    D_0047EF70 = 0x3F800000;
    D_0047EF74 = 0x3F800000;
    D_0047EF78 = 0x3F800000;
    D_00482778 = 0;
    TaskTableSetFlagRelated_1f53d0(0);
}
