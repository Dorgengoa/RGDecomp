/* rgp:protos */
#define RGP_SELF_MapMgrCaptionDraw_1e2620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapMgrCaptionDraw_1e2620(void *p4)
{
    return (MapCaptionDraw_33f330((u8 *)p4 + 0x18E8), (s32)0);
}
