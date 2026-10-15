#include "types.h"

typedef struct {
    u8 pad0[0x1];
} Buf00268DC0;

s32 ArchiveGetFileByPath_1c2800(s32, s32, Buf00268DC0 *);
s32 EvSceneObjReloadCfg_268f10(s32, s32, s32, s32);
s32 ScriptGetCodeAddr_26a200(s32);
s32 ScriptGetInt_26a2a0(s32);
s32 FileLoadCached_26a6c0(s32, s32);

s32 EvCmdEvSceneObjReloadCfg_268dc0(s64 *arg0, s32 arg1) {
    Buf00268DC0 sp6C;
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    s32 r;

    if (arg1 == 4) {
        v1 = ScriptGetInt_26a2a0((s32)arg0++);
        v2 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v3 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v4 = ScriptGetInt_26a2a0((s32)arg0);
        r = FileLoadCached_26a6c0(v2, 0);
        if (r != 0) {
            return EvSceneObjReloadCfg_268f10(v1, v3, v4, r);
        }
        return 0;
    } else if (arg1 == 5) {
        v0 = ScriptGetInt_26a2a0((s32)arg0++);
        v1 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v2 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v3 = ScriptGetCodeAddr_26a200((s32)arg0++);
        v4 = ScriptGetInt_26a2a0((s32)arg0);
        r = FileLoadCached_26a6c0(v1, 0);
        if (r == 0) {
            return 0;
        }
        r = ArchiveGetFileByPath_1c2800(r, v2, &sp6C);
        if (r != 0) {
            return EvSceneObjReloadCfg_268f10(v0, v3, v4, r);
        }
        return 0;
    }
    return 1;
}
