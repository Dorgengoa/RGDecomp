/* rgp:protos */
#define RGP_SELF_MapDefCmdMapBox_1eb2d0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B080[0x400];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481910;

typedef struct {
    u8 pad0[0x3E];
    s16 n;
    u8 pad40[0xC];
    s32 tbl;
} P1eb;

s32 MapDefCmdMapBox_1eb2d0(s32 arg0, s32 arg1)
{
    P1eb *p;
    s8 *name;
    s32 var_2;
    s32 h;
    s16 idx;
    f32 scale;
    f32 x;
    f32 y;

    if (arg1 != 8) {
        return 0;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) return 1;
    p = (P1eb *)MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (p->tbl == 0 || p->n <= D_00481910) {
        return 1;
    }
    GetGameData_1fede0();
    p = (P1eb *)(p->tbl + (D_00481910 * 0x50));
    MapBoxSetNumMaybe_1ddee0((s32)p, ScriptArgGetInt_1ecbe0(arg0));
    name = ((s8 *)ScriptArgGetStr_1ecb80(arg0 + 8));
    if (name != NULL && *name != 0) {
        h = MapAreaFindBlockByName_1dc700(D_004818FC, name);
        if (h != 0) {
            var_2 = ((short)MapDataGetId_1e7bd0(h));
        } else {
            var_2 = -1;
        }
        MapBoxSetBlockId_1dded0((s32)p, var_2);
    } else {
        MapBoxSetBlockId_1dded0((s32)p, -1);
    }
    scale = (*(f32 *)D_0045B080);
    x = scale * ScriptArgGetFloat_1ecba0(arg0 + 0x10);
    y = scale * ScriptArgGetFloat_1ecba0(arg0 + 0x18);
    AreaBoxSetCorner0_1e97a0((s32)p, x, y, scale * ScriptArgGetFloat_1ecba0(arg0 + 0x20));
    x = scale * ScriptArgGetFloat_1ecba0(arg0 + 0x28);
    y = scale * ScriptArgGetFloat_1ecba0(arg0 + 0x30);
    AreaBoxSetCorner1_1e9790((s32)p, x, y, scale * ScriptArgGetFloat_1ecba0(arg0 + 0x38));
    AreaBoxCalc_1e9650((s32)p);
    D_00481910 += 1;
    return 1;
}
