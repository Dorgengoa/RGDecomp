/* rgp:protos */
#define RGP_SELF_MenuTestResRelease_2038c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481C58;

void MenuTestResRelease_2038c0(void)
{
    s32 r0;

    D_00481C58 = 0;
    r0 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r0, 0x32F);
    MenuTestStackRelease_206530();
}
