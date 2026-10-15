#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32);
extern u8 *GetDrawCtxNameTable_15de40(void);
extern s32 ArchiveGetFileByPath_1c2800(s32, s32, void *);
extern s32 RecStackGetSlot_1c4330(s32, s32);
extern void *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ScriptGetCodeAddr_26a200(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 FileLoadCached_26a6c0(s32, s32);
extern s32 memset(void *, s32, s32);
extern s32 strcpy(void *, void *);
extern void InfoCfgParseModelsThunk_1abfe0(void *, void *);
extern u8 D_0045EF98[0x400];
extern s32 D_00481F78;
extern s32 D_004BD980[];

s32 EvCmdObjLoadInfoCfgModels_25c580(s64 *arg0, s32 arg1)
{
    s32 out;
    u8 name[0x20];
    u8 pk[0x88];
    s32 cat;
    s32 flags;
    s32 tex;
    s32 slot;
    s32 req;
    s32 e4dc;
    s32 res;
    s32 id;
    s32 r;
    u8 *player;
    u8 *info;

    req = 0;
    if (arg1 == 4) {
        cat = ScriptGetInt_26a2a0((s32)arg0++);
        slot = ScriptGetCodeAddr_26a200((s32)arg0++);
        flags = ScriptGetCodeAddr_26a200((s32)arg0++);
        tex = ScriptGetInt_26a2a0((s32)arg0);
    } else if (arg1 == 5) {
        cat = ScriptGetInt_26a2a0((s32)arg0++);
        req = ScriptGetCodeAddr_26a200((s32)arg0++);
        slot = ScriptGetCodeAddr_26a200((s32)arg0++);
        flags = ScriptGetCodeAddr_26a200((s32)arg0++);
        tex = ScriptGetInt_26a2a0((s32)arg0);
    }
    if ((player = (u8 *)ObjRecGetLiveObject_1c4a90(D_00481F78, tex)) == NULL) {
        return 0;
    }
    e4dc = *(s32 *)(player + 0x4DC);
    if (e4dc < 0) {
        return 0;
    }
    res = RecStackGetSlot_1c4330(D_00481F78, D_004BD980[cat]);
    if (res == 0) {
        return 0;
    }
    if (req == 0) {
        if ((id = FileLoadCached_26a6c0(slot, 0)) == 0) {
            return 0;
        }
    } else {
        r = FileLoadCached_26a6c0(req, 0);
        if (r == 0) {
            return 0;
        }
        id = ArchiveGetFileByPath_1c2800(r, slot, &out);
    }
    Sprintf_1343b8(name, D_0045EF98, tex);
    info = GetDrawCtxNameTable_15de40();
    if (tex >= 0x40) {
        strcpy(info + 0x1E4, name);
    }
    memset(pk, 0, 0x88);
    *(u8 **)(pk + 0x2C) = pk + 0x40;
    *(u8 **)(pk + 0x38) = pk + 0x60;
    *(s32 *)(pk + 0x30) = 8;
    *(s32 *)(pk + 0x18) = 1;
    *(s32 *)(pk + 0x3C) = 8;
    *(s32 *)(pk + 0x0) = id;
    *(s32 *)(pk + 0x4) = flags;
    *(s32 *)(pk + 0x14) = e4dc;
    *(s32 *)(pk + 0x8) = res;
    *(s32 *)(pk + 0xC) = res;
    *(s32 *)(pk + 0x10) = res;
    InfoCfgParseModelsThunk_1abfe0(player, pk);
    if (tex >= 0x40) {
        *(info + 0x1E4) = 0;
    }
    return 1;
}
