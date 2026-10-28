/* rgp:protos */
#define RGP_SELF_AiCmdCharaReqAttack1Maybe_2cbc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004DB92C[3];
/*rgp*/

s32 AiCmdCharaReqAttack1Maybe_2cbc10(void)
{
    void *g;

    g = D_004DB92C[0];
    if (g == 0) {
        return 0;
    }
    CharaSetFlags_212470(g, 0x80000000000000);
    return 1;
}
