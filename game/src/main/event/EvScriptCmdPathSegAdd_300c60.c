/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathSegAdd_300c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } E8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00451EB0[0x10];
extern f32 D_0045B078[4];
extern E8 *D_00482848;
extern s32 D_0048284C;

typedef struct { u8 pad[0x18]; s32 unk18; } Obj300;

s32 EvScriptCmdPathSegAdd_300c60(void *arg0, s32 arg1)
{
    E8 *p;
    s32 var_19;
    s32 t17;
    s32 t18;
    f32 f;

    if (arg1 != 4) {
        return 0;
    }
    if (D_00482848 == 0 || D_0048284C >= 0x40) {
        return 1;
    }
    p = D_00482848 + D_0048284C;
    if (((Obj300 *)arg0)->unk18 == 2) {
        f = ScriptArgGetFloat_301a20((u8 *)arg0 + 0x18);
    var_19 = (s32) (f * D_0045B078[0]);
    } else {
        var_19 = ScriptArgGetInt_301a60((u8 *)arg0 + 0x18);
    }
    t18 = ParseFlagNames_1ca700(ScriptArgGetStr_301a00(arg0), D_00451EB0, 0);
    t17 = ScriptArgGetInt_301a60((u8 *)arg0 + 0x8);
    EventPathSegSet_2e47b0(p, t18, t17, ScriptArgGetInt_301a60((u8 *)arg0 + 0x10), var_19);
    D_0048284C += 1;
    return 1;
}
