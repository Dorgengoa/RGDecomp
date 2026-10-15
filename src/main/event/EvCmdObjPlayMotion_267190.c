#include "types.h"

extern void ModelObjPlayMotionByName_1867a0(s32, void *, s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 ModelHasMotion_20a5b0(s32, void *);
extern s32 EventSceneGetObj_2676e0(s32);
extern void *ScriptGetCodeAddr_26a200(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 strcmp(void *, void *);
extern void strcpy(void *, void *);
extern u8 D_0045EE48[];
extern u8 D_0045EE50[];
extern u8 D_0045EE58[];
extern u8 D_0045EE60[];
extern u8 D_0045EE68[];

s32 EvCmdObjPlayMotion_267190(s64 *arg0, s32 arg1)
{
    s32 o;
    u8 sp60[0x20];
    void *name;
    s32 r;

    r = 0;
    o = EventSceneGetObj_2676e0(ScriptGetInt_26a2a0((s32)arg0++));
    name = ScriptGetCodeAddr_26a200((s32)arg0++);
    if (arg1 >= 3) {
        r = ScriptGetInt_26a2a0((s32)arg0);
    }
    if (o == 0) {
        return 0;
    }
    strcpy(sp60, name);
    if (GetGameMode_1f59c0() == 0xA || GetGameMode_1f59c0() == 9) {
        if (ModelHasMotion_20a5b0(o, D_0045EE48) != 0 && ModelHasMotion_20a5b0(o, D_0045EE50) != 0) {
            if (strcmp(sp60, D_0045EE58) == 0) {
                strcpy(sp60, D_0045EE48);
            }
            if (strcmp(sp60, D_0045EE60) == 0) {
                strcpy(sp60, D_0045EE68);
            }
        }
    }
    ModelObjPlayMotionByName_1867a0(o, sp60, r);
    return 1;
}
