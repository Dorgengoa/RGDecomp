#include "types.h"

extern s32 CharaGetTargetRef_214a30(s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern void TargetRefSetAttachPoint_2e65f0(s32, s32, s32, s32);
extern s32 D_004DB92C[];

s32 AiCmdSetTargetById_2c6290(s32 arg0) {
    s32 t2;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    t2 = CharaGetTargetRef_214a30(D_004DB92C[0]);
    if (t2 == 0) {
        return 0;
    }
    TargetRefSetAttachPoint_2e65f0(t2, ScriptSlotGetInt_2cc9c0(arg0), 0x82, 0);
    return 1;
}
