#include "types.h"

typedef struct {
    u8 pad0[0x54];
    s32 unk54;
} Ctx;

typedef struct {
    u8 padA[0xA];
    u8 unkA;
    u8 pad0xB[0x1C - 0xB];
    s32 unk1C;
} Obj3;

extern Ctx *GetGameData_1fede0(void);
extern s32 MesMgrGetSlotWin_266af0(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 MesWinSetName_271300(s32, void *);
extern s32 MesWinSetNameShown_271390(s32, s32);
extern s32 MesWinSetTextWithEnd_2726c0(s32, s32, s32);
extern s32 MesWinSetSeEnabled_272b50(s32, s32);
extern s32 MesWinGetTextFileSize_274e30(s32);
extern s32 MesWinGetTextFile_274e40(s32);
extern s32 MesWinSetTextFile_274e50(s32, s32, s32);
extern s32 MesWinSetMode_276e00(s32, s32);
extern s32 MesWinInit_276f20(s32);
extern s32 TextFindAtLabelLine_2772f0(s32, s32, s32);
typedef struct {
    u8 padA[0xA];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 pad0xB[0x1C - 0xB];
    s32 unk1C;
} Obj3b;
extern Obj3b *GetInteractState_27a650(void);
extern u8 D_0045F0E0[0x400];

s32 EvCmdMesWinSetTextMaybe_260800(s64 *arg0, s32 arg1) {
    Obj3b *o;
    Ctx *ctx;
    s32 h;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 r;
    s32 e40;
    s32 e30;
    s32 n;

    if (arg1 < 4) {
        return 0;
    }
    h = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
    if (h == 0) {
        return 0;
    }
    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0++);
    c = ScriptGetInt_26a2a0((s32)arg0++);
    d = -1;
    if (arg1 >= 5) {
        d = ScriptGetInt_26a2a0((s32)arg0);
    }
    ctx = GetGameData_1fede0();
    r = 0;
    if (a >= 0 && b >= 0 && c >= 0) {
        r = ctx->unk54;
    }
    if (r == 0) {
        MesWinSetTextWithEnd_2726c0(h, 0, 0);
    } else {
        o = GetInteractState_27a650();
    if (o->b1 && !o->b2 && d > 0) {
        e40 = MesWinGetTextFile_274e40(h);
        if (e40 != 0) {
            e30 = MesWinGetTextFileSize_274e30(h);
            if (e30 > 0) {
                r = TextFindAtLabelLine_2772f0(e40, e30, d);
            }
        }
    }
    e40 = MesWinGetTextFile_274e40(h);
    e30 = MesWinGetTextFileSize_274e30(h);
    MesWinInit_276f20(h);
    MesWinSetMode_276e00(h, 0);
    if (o->b0) {
        MesWinSetNameShown_271390(h, 0);
        MesWinSetName_271300(h, D_0045F0E0);
    } else {
        MesWinSetNameShown_271390(h, 1);
        MesWinSetName_271300(h, (void *)o->unk1C);
    }
    MesWinSetSeEnabled_272b50(h, 1);
    MesWinSetTextWithEnd_2726c0(h, r, 0);
    MesWinSetTextFile_274e50(h, e40, e30);
    }
    return 1;
}
