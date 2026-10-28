/* rgp:protos */
#define RGP_SELF_insect_InsectMsgCenterX_512b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512B10 -- 21 instructions.  Both incoming integer parameters are
 * forwarded untouched to insect_InsectMsgGet_512b70, whose result is the second
 * argument of insect_InsectMsgTextWidth_512ab0 -- a NESTED call expression, which is what
 * keeps $6 alive in $16 across the first call. */

/*rgp*/
/*rgp*/

s32 insect_InsectMsgCenterX_512b10(void *h, s32 id, s32 w)
{
    return (w - insect_InsectMsgTextWidth_512ab0(h, ((s32)insect_InsectMsgGet_512b70(h, id)), 2)) / 2;
}
