/* rgp:protos */
#define RGP_SELF_EvScriptCmdVehicleInit_2fef20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004E6EC0[];
extern void *D_00482878;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


s32 EvScriptCmdVehicleInit_2fef20(u8 *p, s32 argc)
{
    EvScriptTemplatesReset_301c20();
    if (argc != 7 && argc != 8) {
        return 0;
    }
    D_00482878 = EventScratchAlloc_301b00(0xC80);
    if (D_00482878 == 0) {
        return 1;
    }
    switch (argc) {
    case 7:
        ObjTypeVehicleInitByName_3382c0(D_004E6EC0, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0, 0,
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     ScriptArgGetAreaId_3019b0(p + 0x18),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x20)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x30)),
                     D_00482878, 0);
        break;
    case 8:
        ObjTypeVehicleInitByName_3382c0(D_004E6EC0, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x38)),
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     ScriptArgGetAreaId_3019b0(p + 0x18),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x20)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x30)),
                     D_00482878, 0);
        break;
    }
    return 1;
}
