/* rgp:protos */
#define RGP_SELF_AiCmdCharaResetStateMaybe_2cb380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004DB92C[3];
/*rgp*/

s32 AiCmdCharaResetStateMaybe_2cb380(void)
{
    void *p;

    p = D_004DB92C[0];
    if (p != 0) {
        CharaResetStateMaybe_212c50(p);
    }
    return 1;
}
