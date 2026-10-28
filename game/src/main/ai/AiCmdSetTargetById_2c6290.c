/* rgp:protos */
#define RGP_SELF_AiCmdSetTargetById_2c6290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB92C[];

s32 AiCmdSetTargetById_2c6290(s32 arg0) {
    s32 t2;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    t2 = ((s32)CharaGetTargetRef_214a30(D_004DB92C[0]));
    if (t2 == 0) {
        return 0;
    }
    TargetRefSetAttachPoint_2e65f0(t2, ScriptSlotGetInt_2cc9c0(arg0), 0x82, 0);
    return 1;
}
