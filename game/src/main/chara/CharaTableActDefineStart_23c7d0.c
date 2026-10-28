/* rgp:protos */
#define RGP_SELF_CharaTableActDefineStart_23c7d0 1
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
extern u8 D_0044C3E0[];
extern s32 D_00481E70;
extern s32 D_00481EA0;
extern s32 D_00481EA8;
extern s32 D_00481EB0;
extern s32 D_00481EB8;
extern s32 D_00481EC0;
extern s32 D_00481EC8;
extern s32 D_00481ED0;
extern s32 D_00481ED8;
extern s32 D_00481EEC;
extern s32 D_00481EFC;
extern u8 D_004BCDE0[];

s32 CharaTableActDefineStart_23c7d0(s32 arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 e;
    s32 d;

    ActCfgTablesReset_23fdd0();
    if (arg1 != 1 && arg1 != 2) {
        return 0;
    }
    if (D_00481EEC == 0) {
        return 1;
    }
    GetCurrentScene_1f5be0();
    a = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
    b = 0;
    if (arg1 > 1) {
        b = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C3E0, 0);
    }
    e = ScriptArenaAlloc16_23fcb0(0x440);
    d = ScriptArenaAlloc16_23fcb0(0x180);
    c = ScriptArenaAlloc16_23fcb0(0x180);
    CharaTableInit_225660(D_004BCDE0, a, b, (long long)(0), (long long)(0), e, 0, d, 0, c, 0, ScriptArenaAlloc16_23fcb0(0x100), 0);
    D_00481EA0 = ScriptArenaAlloc16_23fcb0(0x80);
    D_00481EA8 = ScriptArenaAlloc16_23fcb0(0x400);
    D_00481EB0 = ScriptArenaAlloc16_23fcb0(0x800);
    D_00481EB8 = ScriptArenaAlloc16_23fcb0(0x400);
    D_00481EC0 = ScriptArenaAlloc16_23fcb0(0x500);
    D_00481EC8 = ScriptArenaAlloc16_23fcb0(0x400);
    D_00481ED0 = ScriptArenaAlloc16_23fcb0(0x500);
    D_00481ED8 = ScriptArenaAlloc16_23fcb0(0x500);
    D_00481E70 = ScriptArenaAlloc16_23fcb0(0x2800);
    D_00481EFC = 2;
    return 1;
}
