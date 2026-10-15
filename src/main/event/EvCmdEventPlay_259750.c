#include "types.h"

typedef struct Value {
    s32 type;
    s32 v;
} Value;

extern s32 ScriptGetCodeAddr_26a200(Value *);
extern s32 ScriptGetInt_26a2a0(Value *);
extern void Sprintf_1343b8(char *, const char *, s32);
extern void PathLocalize_1c28c0(char *, char *);
extern s32 FileLoadCached_26a6c0(s32, s32 *);
extern void ScriptArgInitInt_26a1b0(Value *, s32);
extern void ScriptArgInitCodeAddr_26a1a0(Value *, void *);
extern s32 EvCmdEventStackPush_25d1b0(Value *, s32);
extern s32 EvCmdMesWinLoadFile_265c00(Value *, s32);
extern s32 EvCmdMesWinSetStyle_266400(Value *, s32);
extern s32 EvCmdEventPlayerCreate_261220(Value *, s32);
extern s32 EvCmdResHandlesFreeAll_268760(s32, s32);
extern s32 EvCmdEventPlayerQueueEntry_2610d0(Value *, s32);
extern char D_0045EE18[];
extern char D_0045EE28[];
extern char D_0045EE38[];

s32 EvCmdEventPlay_259750(Value *args, s32 argc) {
    s32 found;
    Value a1[1];
    char b0[0x20];
    char c0[0x20];
    char b1[0x20];
    char c1[0x20];
    char b2[0x20];
    char c2[0x20];
    Value a4[4];
    Value a3[2];
    Value a2[4];
    Value a5[2];
    s32 h;
    s32 name0;
    s32 name1;
    s32 name2;
    s32 n;
    s32 v;
    s32 obj;

    if (argc < 2) {
        return 0;
    }
    h = ScriptGetCodeAddr_26a200(args++);
    name0 = ScriptGetCodeAddr_26a200(args++);
    n = 1;
    name1 = name0;
    name2 = name0;
    if (argc >= 3) {
        v = ScriptGetCodeAddr_26a200(args++);
        if (v != 0) {
            name1 = v;
        }
    }
    if (argc >= 4) {
        v = ScriptGetCodeAddr_26a200(args++);
        if (v != 0) {
            name2 = v;
        }
    }
    if (argc >= 5) {
        n = ScriptGetInt_26a2a0(args);
    }
    Sprintf_1343b8(b0, D_0045EE18, name0);
    Sprintf_1343b8(b1, D_0045EE28, name1);
    Sprintf_1343b8(b2, D_0045EE38, name2);
    PathLocalize_1c28c0(c0, b0);
    PathLocalize_1c28c0(c1, b1);
    PathLocalize_1c28c0(c2, b2);
    found = 0;
    obj = 0;
    if (h != 0) {
        obj = FileLoadCached_26a6c0(h, &found);
        if (obj == 0) {
            return 0;
        }
    }
    ScriptArgInitInt_26a1b0(&a1[0], 4);
    if (EvCmdEventStackPush_25d1b0(a1, 1) == 0) {
        return 0;
    }
    ScriptArgInitInt_26a1b0(&a4[0], 6);
    ScriptArgInitInt_26a1b0(&a4[1], 4);
    ScriptArgInitCodeAddr_26a1a0(&a4[2], c2);
    ScriptArgInitCodeAddr_26a1a0(&a4[3], (void *)obj);
    if (EvCmdMesWinLoadFile_265c00(a4, 4) == 0) {
        return 0;
    }
    ScriptArgInitInt_26a1b0(&a3[0], 6);
    ScriptArgInitInt_26a1b0(&a3[1], 1);
    if (EvCmdMesWinSetStyle_266400(a3, 2) == 0) {
        return 0;
    }
    ScriptArgInitInt_26a1b0(&a2[0], 4);
    ScriptArgInitCodeAddr_26a1a0(&a2[1], c1);
    ScriptArgInitCodeAddr_26a1a0(&a2[2], c0);
    ScriptArgInitCodeAddr_26a1a0(&a2[3], (void *)obj);
    if (EvCmdEventPlayerCreate_261220(a2, 4) == 0) {
        return 0;
    }
    if (EvCmdResHandlesFreeAll_268760(0, 0) == 0) {
        return 0;
    }
    ScriptArgInitInt_26a1b0(&a5[0], 0x3E8);
    ScriptArgInitInt_26a1b0(&a5[1], n);
    return EvCmdEventPlayerQueueEntry_2610d0(a5, 2) != 0;
}
