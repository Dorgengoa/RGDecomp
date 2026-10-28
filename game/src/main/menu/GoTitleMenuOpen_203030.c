/* rgp:protos */
#define RGP_SELF_GoTitleMenuOpen_203030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GoTitleMenuOpen_203030(void)
{
    MenuGoTitleStackInit_2062a0(0x10);
    GoTitleMenuInit_39bfe0();
}
