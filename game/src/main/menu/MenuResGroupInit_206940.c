/* rgp:protos */
#define RGP_SELF_MenuResGroupInit_206940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MenuResGroupInit_206940(void)
{
    s32 r0;

    r0 = ((s32)GetMenuResGroup_206a40());
    ResGroupReset_42c760(r0);
    ResGroupUnloadGroup_42b650(r0, 0);
    MenuResGroupLoadCommon_42bc30(r0);
}
