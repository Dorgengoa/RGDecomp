/* rgp:protos */
#define RGP_SELF_InsectCageMenuSelectEntry_390d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004E94E0[];

/*rgp*/

s32 InsectCageMenuSelectEntry_390d40(s32 a4, s32 a5)
{
    return UiEntryListSelectByTag_28ea90(D_004E94E0, a4, a5);
}
