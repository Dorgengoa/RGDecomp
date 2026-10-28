/* rgp:protos */
#define RGP_SELF_insect_InsectIsJingleDoneMaybe_510780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510780 -- 72 bytes, 18 instructions. */

/*rgp*/
/*rgp*/

s32 insect_InsectIsJingleDoneMaybe_510780(void)
{
    void *p;

    p = GetStreamMgr_207ea0();
    if (p != 0) {
        if (StreamMgrChanGetStatus_1d65f0(p, 1) == 2) {
            return 1;
        }
    }
    return 0;
}
