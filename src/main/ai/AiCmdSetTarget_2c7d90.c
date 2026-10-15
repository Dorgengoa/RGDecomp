#include "types.h"

s32 CharaGetAi_214a10(void *);                           /* extern */
s32 CharaGetTargetRef_214a30(void *);                           /* extern */
s32 AiSetTargetCharaId_2c0f10(s32, s32);                           /* extern */
s32 AiGetTargetCharaId_2c0fd0(s32);                                /* extern */
s32 ScriptSlotGetInt_2cc9c0(s32);                              /* extern */
s32 TargetRefResolve_2e5ed0(s32, s32);                             /* extern */
s32 TargetRefSetAttachPoint_2e65f0(s32, s32, s32, s32);                     /* extern */
extern u8 D_004DB92C[0x400];

s32 AiCmdSetTarget_2c7d90(s32 arg0, s32 arg1) {
s32 temp_2_2;
s32 temp_2;
s32 temp_16;
if (arg1 != 1) {
        return 0;
    }
    if ((*(void * *)D_004DB92C) == NULL) {
        return 0;
    }
    temp_2 = CharaGetAi_214a10((*(void * *)D_004DB92C));
    if (temp_2 == 0) {
        return 0;
    }
    temp_2_2 = ScriptSlotGetInt_2cc9c0(arg0);
    if (temp_2_2 >= 0) {
        AiGetTargetCharaId_2c0fd0(temp_2);
        AiSetTargetCharaId_2c0f10(temp_2, temp_2_2);
        temp_16 = CharaGetTargetRef_214a30((*(void * *)D_004DB92C));
        if (temp_2_2 < 0xC) {
            TargetRefSetAttachPoint_2e65f0(temp_16, temp_2_2, 0x64, 0);
        } else {
            TargetRefSetAttachPoint_2e65f0(temp_16, temp_2_2, 0x82, 0);
        }
        TargetRefResolve_2e5ed0(temp_16, 0);
        (*(s32 *)((u8 *)((*(void * *)D_004DB92C)) + 0xA44)) = (s32) ((*(s32 *)((u8 *)((*(void * *)D_004DB92C)) + 0xA44)) | 0x8000);
    } else {
        (*(s32 *)((u8 *)((*(void * *)D_004DB92C)) + 0xA44)) = (s32) ((*(s32 *)((u8 *)((*(void * *)D_004DB92C)) + 0xA44)) & 0xFFFF7FFF);
    }
    return 1;
    return 0;
}
