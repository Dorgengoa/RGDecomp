/* rgp:protos */
#define RGP_SELF_EasyMenuOpen_2030d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EasyMenuOpen_2030d0(void)
{
    MenuEasyStackInit_206360(0x10);
    LeaderSwitchMenuInit_39d210();
}
