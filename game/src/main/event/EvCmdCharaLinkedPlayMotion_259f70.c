/* rgp:protos */
#define RGP_SELF_EvCmdCharaLinkedPlayMotion_259f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(void *, void *);
extern char *strcpy(void *, void *);
extern u8 D_0045EE48[0x400];
extern u8 D_0045EE50[0x400];
extern u8 D_0045EE58[0x400];
extern u8 D_0045EE60[0x400];
extern u8 D_0045EE68[0x400];

s32 EvCmdCharaLinkedPlayMotion_259f70(s64 *arg0, s32 arg1)
{
    s32 sp90[0x20] __attribute__((aligned(16)));
    u8 sp70[0x20] __attribute__((aligned(16)));
    s32 temp_16_2;
    s32 temp_17;
    s32 temp_21;
    void *temp_20;
    s32 var_19;
    s32 var_18;
    s32 temp_2;

    temp_21 = GetCurrentScene_1f5be0();
    temp_17 = ScriptGetInt_26a2a0((s32)arg0++);
    temp_20 = ScriptGetCodeAddr_26a200((s32)arg0++);
    var_19 = 0;
    if (arg1 >= 3) {
        var_19 = ScriptGetInt_26a2a0((s32)arg0);
    }
    temp_16_2 = CharaCollectLinkedIds_25a200(temp_17, sp90);
    for (var_18 = 0; var_18 < temp_16_2; var_18++) {
        temp_2 = ((s32)ObjRecGetLiveObject_1c4a90(temp_21, sp90[var_18]));
        if (temp_2 != 0) {
            strcpy(sp70, temp_20);
            if ((GetGameMode_1f59c0() == 0xA || GetGameMode_1f59c0() == 9) &&
                ModelHasMotion_20a5b0(temp_2, D_0045EE48) != 0 &&
                ModelHasMotion_20a5b0(temp_2, D_0045EE50) != 0) {
                if (strcmp(sp70, D_0045EE58) == 0) {
                    strcpy(sp70, D_0045EE48);
                }
                if (strcmp(sp70, D_0045EE60) == 0) {
                    strcpy(sp70, D_0045EE68);
                }
            }
            ModelObjPlayMotionByName_1867a0(temp_2, sp70, var_19);
        }
    }
    return 1;
}
