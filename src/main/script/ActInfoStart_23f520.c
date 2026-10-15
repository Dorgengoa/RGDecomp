#include "types.h"

typedef struct Elem { u8 b[0x10]; } Elem;

extern u32 ParseFlagNames_1ca700(s32, void *, s32);
extern void GetCurrentScene_1f5be0(void);
extern void ActCfgTableSetMoveCount_223c90(void *, s32);
extern void ActCfgTableInit_224f70(void *, s32, s32, u64, s32, f32, f32,
    s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
    s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
    s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void ActInfoMoveInit_231470(Elem *, s32, f32, f32, f32);
extern s32 ScriptArgGetStr_23fba0(void *);
extern f32 ScriptArgGetFloat_23fbc0(void *);
extern s32 StrDupArena_23fc40(s32);
extern s32 ScriptArenaAlloc16_23fcb0(s32);
extern void ActCfgTablesReset_23fdd0(void);
extern u8 D_0044C000[];
extern u8 D_0044C1F0[];
extern u8 D_0044C530[];
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern f32 D_0047D354;
extern f32 D_0047D404;
extern f32 D_0047D5D0;
extern f32 D_0047DB10;
extern f32 D_0047DB34;
extern f32 D_0047DCB0;
extern f32 D_0047DCB4;
extern f32 D_0047DCB8;
extern f32 D_0047DCBC;
extern f32 D_0047DCC0;
extern f32 D_0047DCC4;
extern f32 D_0047DCC8;
extern s32 D_00481E70;
extern s32 D_00481E78;
extern s32 D_00481E80;
extern s32 D_00481E88;
extern s32 D_00481E90;
extern s32 D_00481E98;
extern s32 D_00481EEC;
extern s32 D_00481EF8;
extern u8 D_004BCE20[];
extern Elem *D_004BCE44[];

s32 ActInfoStart_23f520(u8 *self, s32 mode) {
    f32 a;
    f32 b;
    s32 h;
    u64 key;
    s32 c;
    s32 m0;
    s32 m1;
    s32 m2;
    s32 m3;
    s32 m4;
    s32 m5;
    s32 m6;
    s32 m7;
    s32 m8;
    s32 m9;
    s32 m10;
    s32 m11;
    s32 m12;
    s32 m13;
    Elem *p;

    ActCfgTablesReset_23fdd0();
    if (mode != 3 && mode != 4 && mode != 5) {
        return 0;
    }
    if (D_00481EEC != 0) {
        return 1;
    }
    GetCurrentScene_1f5be0();
    if (mode >= 4) {
        a = ScriptArgGetFloat_23fbc0(self + 0x18);
    } else {
        a = 0.0f;
    }
    if (mode >= 5) {
        b = ScriptArgGetFloat_23fbc0(self + 0x20);
    } else {
        b = 1.0f;
    }
    h = StrDupArena_23fc40(ScriptArgGetStr_23fba0(self));
    key = (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self + 8), D_0044C000, 0) << 32;
    key |= (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self + 8), D_0044C1F0, 0);
    c = ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self + 0x10), D_0044C530, 0);
    m0 = ScriptArenaAlloc16_23fcb0(0x100);
    m1 = ScriptArenaAlloc16_23fcb0(0x200);
    m2 = ScriptArenaAlloc16_23fcb0(0x100);
    m3 = ScriptArenaAlloc16_23fcb0(0x300);
    m4 = ScriptArenaAlloc16_23fcb0(0x400);
    m5 = ScriptArenaAlloc16_23fcb0(0x600);
    m6 = ScriptArenaAlloc16_23fcb0(0x500);
    m7 = ScriptArenaAlloc16_23fcb0(0x100);
    m8 = ScriptArenaAlloc16_23fcb0(0x3E00);
    m9 = ScriptArenaAlloc16_23fcb0(0x300);
    m10 = ScriptArenaAlloc16_23fcb0(0x180);
    m11 = ScriptArenaAlloc16_23fcb0(0x180);
    m12 = ScriptArenaAlloc16_23fcb0(0x100);
    m13 = ScriptArenaAlloc16_23fcb0(0x180);
    ActCfgTableInit_224f70(D_004BCE20, D_00481EF8, h, key, c, a, b,
        m0, 0, m1, 0, m2, 0, m3, 0, m4, 0,
        m5, 0, m6, 0, m7, 0, m8, 0, m9, 0,
        m10, 0, m11, 0, m12, 0, m13, 0, ScriptArenaAlloc16_23fcb0(0x30), 0);
    D_00481E90 = ScriptArenaAlloc16_23fcb0(0x400);
    D_00481E98 = ScriptArenaAlloc16_23fcb0(0x600);
    D_00481E78 = ScriptArenaAlloc16_23fcb0(0x1800);
    D_00481E70 = ScriptArenaAlloc16_23fcb0(0x2800);
    D_00481E80 = ScriptArenaAlloc16_23fcb0(0x800);
    D_00481E88 = ScriptArenaAlloc16_23fcb0(0x600);
    p = D_004BCE44[0];
    ActInfoMoveInit_231470(&p[0], 0x65, D_0047DCB0, 0.25f, 0.0f);
    ActInfoMoveInit_231470(&p[1], 0x66, D_0047DCB4, D_0047DCB8, D_0047DCBC);
    ActInfoMoveInit_231470(&p[2], 0x67, D_0047DB10, D_0047DCB8, D_0047D354);
    ActInfoMoveInit_231470(&p[3], 4, D_0047DCC0, D_0047D5D0, D_0047DCBC);
    ActInfoMoveInit_231470(&p[4], 5, D_0047DCC4, D_0047DCB8, 2.0f);
    ActInfoMoveInit_231470(&p[5], 0x6A, D_0047DB10, D_0047DCB8, D_0047DCC8);
    ActInfoMoveInit_231470(&p[6], 0x64, D_0047D404, D_0047D288, D_0047DCBC);
    ActInfoMoveInit_231470(&p[7], 0x68, D_0047D1FC, D_0047DB34, D_0047DCBC);
    ActInfoMoveInit_231470(&p[8], 0x69, D_0047DCC0, D_0047D5D0, D_0047D354);
    ActCfgTableSetMoveCount_223c90(D_004BCE20, &p[9] - D_004BCE44[0]);
    return 1;
}
