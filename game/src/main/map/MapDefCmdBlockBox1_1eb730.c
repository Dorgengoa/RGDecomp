/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockBox1_1eb730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
    u8 pad0xC[0x11 - 0xC];
    u8 unk11;
} Elem0044;

typedef struct {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3C[0x44 - 0x3C];
    s32 unk44;
} Obj001dcf20;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_00481908;

s32 MapDefCmdBlockBox1_1eb730(s32 arg0, s32 arg1)
{
    f32 k;
    f32 x;
    f32 y;
    s32 e;
    s32 list;
    s32 tbl;
    Obj001dcf20 *o;
    Elem0044 *el;

    if (arg1 != 6) {
        return 1;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) return 1;
    o = ((Obj001dcf20 *)MapAreaDefGetRecTable_1dcf20(D_004818FC));
    if (o->unk44 == 0 || o->unk3A <= D_00481904) {
        return 1;
    }
    el = ((Elem0044 *)MapBlockGetInfo_1e00b0(o->unk44 + D_00481904 * 0xCC));
    if (el->unk8 == 0 || (s8)el->unk11 <= D_00481908) {
        return 1;
    }
    e = el->unk8 + D_00481908 * 0x4C;
    k = D_0045B080[0];
    x = k * ScriptArgGetFloat_1ecba0(arg0);
    y = k * ScriptArgGetFloat_1ecba0(arg0 + 8);
    AreaBoxSetCorner0_1e97a0(e, x, y, k * ScriptArgGetFloat_1ecba0(arg0 + 0x10));
    x = k * ScriptArgGetFloat_1ecba0(arg0 + 0x18);
    y = k * ScriptArgGetFloat_1ecba0(arg0 + 0x20);
    AreaBoxSetCorner1_1e9790(e, x, y, k * ScriptArgGetFloat_1ecba0(arg0 + 0x28));
    AreaBoxCalc_1e9650(e);
    D_00481908 += 1;
    return 1;
}
