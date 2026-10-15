#include "types.h"

void *ObjRecGetLiveObject_1c4a90(s32, s32); /* extern */
s32 GetCurrentScene_1f5be0(void); /* extern */
void ScriptSetRefFloat_26a1c0(s32, f32); /* extern */
s32 ScriptGetInt_26a2a0(s32); /* extern */
extern const f32 D_0045B080;
extern f32 D_0047DD20;

s32 EvCmdObjGetScaledHeight_2691f0(s32 arg0, s32 arg1) {
    f32 var_f20;
    s32 temp_16;
    void *temp_2;

    if (arg1 < 2) {
        return 0;
    }
    var_f20 = 0.0f;
    temp_16 = GetCurrentScene_1f5be0();
    temp_2 = ObjRecGetLiveObject_1c4a90(temp_16, ScriptGetInt_26a2a0(arg0));
    if (temp_2 != NULL) {
        f32 a = D_0045B080;
        f32 b = D_0047DD20;
        var_f20 = (*(f32 *)((u8 *)temp_2 + 0x4CC)) * (b * a);
    }
    ScriptSetRefFloat_26a1c0(arg0 + 8, var_f20);
    return 1;
}
