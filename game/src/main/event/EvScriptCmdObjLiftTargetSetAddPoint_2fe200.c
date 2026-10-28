/* rgp:protos */
#define RGP_SELF_EvScriptCmdObjLiftTargetSetAddPoint_2fe200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Under the PS2 EABI the GPR and FPR argument pools are independent, so the
   interleaved int/float argument list below lands exactly as retail has it:
   the eight GPR values go to $4..$11 and the seven floats to $f12..$f18, and
   the ORDER OF EVALUATION (strictly left to right) is what the listing shows. */

extern u8 D_004E7000[];
extern u8 *D_00482888;
extern s32 D_0048288C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/



s32 EvScriptCmdObjLiftTargetSetAddPoint_2fe200(u8 *p, s32 argc)
{
    u8 *e;

    if (argc != 9 && argc != 0xB) {
        return 0;
    }
    if (D_00482888 == 0 || D_0048288C >= 0x20) {
        return 1;
    }
    e = D_00482888 + D_0048288C * 280;
    switch (argc) {
    case 9:
        EvTargetSetInitPoint_336980(e, ScriptArgGetAreaId_3019b0(p), ((short)TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000))), EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)), -1, 0, -1, 0, ScriptArgGetFloat_301a20(p + 8), ScriptArgGetFloat_301a20(p + 0x10), ScriptArgGetFloat_301a20(p + 0x18), ScriptArgGetFloat_301a20(p + 0x20), ScriptArgGetFloat_301a20(p + 0x30), ScriptArgGetFloat_301a20(p + 0x38), ScriptArgGetFloat_301a20(p + 0x40)






);
        break;
    case 0xB:
        EvTargetSetInitPoint_336980(e, ScriptArgGetAreaId_3019b0(p), ((short)TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000))), EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)), ScriptArgGetAreaId_3019b0(p + 0x48), EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x50)), -1, 0, ScriptArgGetFloat_301a20(p + 8), ScriptArgGetFloat_301a20(p + 0x10), ScriptArgGetFloat_301a20(p + 0x18), ScriptArgGetFloat_301a20(p + 0x20), ScriptArgGetFloat_301a20(p + 0x30), ScriptArgGetFloat_301a20(p + 0x38), ScriptArgGetFloat_301a20(p + 0x40)







);
        break;
    }
    D_0048288C = D_0048288C + 1;
    return 1;
}
