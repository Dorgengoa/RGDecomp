/* rgp:protos */
#define RGP_SELF_normal_InsectEntryGetFee_524220 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00524220 -- clamp the index to [0,6] and hand index+10 to the
 * lookup; the duplicated `addiu $5,$4,0xA` is the branch-likely delay-slot
 * copy of the shared tail, not a second statement. */

extern void *D_004849B4;          /* gp - 0x7BC */

/*rgp*/
/*rgp*/

int normal_InsectEntryGetFee_524220(s32 n)
{
    if (n < 0) {
        n = 0;
    } else if (n >= 6) {
        n = 6;
    }
    return atoi(MsgTableLookup_28aa30(D_004849B4, n + 10));
}
