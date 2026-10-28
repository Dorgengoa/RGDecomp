/* rgp:protos */
#define RGP_SELF_InsectMenuResRelease_203130 1
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

void InsectMenuResRelease_203130(void)
{
    s32 r1;

    InsectMenuClose_397b10();
    r1 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(r1, 0x32D);
    NameTableFreeGroup_158ac0(r1, 0x32E);
}
