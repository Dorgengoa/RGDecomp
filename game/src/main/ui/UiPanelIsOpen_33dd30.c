/* rgp:protos */
#define RGP_SELF_UiPanelIsOpen_33dd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 UiPanelIsOpen_33dd30(s32 a4)
{
    return ((unsigned char)Bit64Test_33de60(a4, 0));
}
