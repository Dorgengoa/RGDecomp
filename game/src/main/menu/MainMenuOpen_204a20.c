/* rgp:protos */
#define RGP_SELF_MainMenuOpen_204a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MainMenuOpen_204a20(void)
{
    MenuReadBufInit_206460(0x120C8);
    MainMenuInit_297510();
}
