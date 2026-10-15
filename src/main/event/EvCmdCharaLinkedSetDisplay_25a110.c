#include "types.h"

s32 ObjRecClearFlag2_1c3e40(s32, s32, s32);
s32 ObjRecSetFlag2_1c3e80(s32, s32, s32);
s32 GetCurrentScene_1f5be0();
s32 CharaCollectLinkedIds_25a200(s32, s32 *, s32);
s32 ScriptSetRefInt_26a1e0(s32, s32);
s32 ScriptGetInt_26a2a0(s32);

s32 EvCmdCharaLinkedSetDisplay_25a110(s64 *arg0, s32 arg1) {
    s32 sp70[0x20];
    s32 ctx;
    s32 flag;
    s32 n;
    s32 i;
    s32 first;

    ctx = GetCurrentScene_1f5be0();
    flag = ScriptGetInt_26a2a0((s32)arg0++);
    n = CharaCollectLinkedIds_25a200(ScriptGetInt_26a2a0((s32)arg0++), sp70, 0x20);
    for (i = 0; i < n; i++) {
        if (flag != 0) {
            ObjRecSetFlag2_1c3e80(ctx, 1, sp70[i]);
        } else {
            ObjRecClearFlag2_1c3e40(ctx, 1, sp70[i]);
        }
    }
    first = sp70[0];
    if (arg1 >= 3) {
        ScriptSetRefInt_26a1e0((s32)arg0, first);
    }
    return 1;
}
