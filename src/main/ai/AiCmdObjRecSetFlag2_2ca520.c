#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern void ObjRecClearFlag2_1c3e40(s32, s32, s32);
extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern u8 D_004DB920[0x400];

s32 AiCmdObjRecSetFlag2_2ca520(s64 *arg0) {
    s32 t17;
    s32 t16;

    t17 = (*(s32 *)D_004DB920);
    t16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    if (!(ScriptSlotGetInt_2cc9c0((s32)arg0) == 0)) {
        ObjRecSetFlag2_1c3e80(t17, 1, t16);
    } else {
        ObjRecClearFlag2_1c3e40(t17, 1, t16);
    }
    return 1;
}
