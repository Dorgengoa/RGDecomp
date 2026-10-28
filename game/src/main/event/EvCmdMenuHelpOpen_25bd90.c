/* rgp:protos */
#define RGP_SELF_EvCmdMenuHelpOpen_25bd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EE80[];
extern u8 D_0045EE90[];

s32 EvCmdMenuHelpOpen_25bd90(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(1, D_0045EE80);
    TaskSetEnabled_27c2a0(1, D_0045EE90);
    r2 = (HelpMenuOpen_2032d0(), (s32)0);
    return 1;
}
