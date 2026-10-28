/* rgp:protos */
#define RGP_SELF_EvScriptCmdEvTargetAddNamed_2fdbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482890;
extern s32 D_00482894;
extern u8 D_004E7110[0x400];

s32 EvScriptCmdEvTargetAddNamed_2fdbe0(s32 arg0, s32 arg1)
{
    s32 b;
    s32 p;
    s32 a;

    if (arg1 != 2) {
        return 0;
    }
    if (D_00482890 == 0 || D_00482894 >= 0x20) {
        return 1;
    }
    p = D_00482890 + D_00482894 * 0x140;
    a = ((short)TargetRefGetId_2e7120(((s32)EvObjGetTargetRef_2f9ca0(D_004E7110))));
    b = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
    EvTargetSetupMaybe_352ae0(p, a, b, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 8)), 0, 0);
    D_00482894 += 1;
    return 1;
}
