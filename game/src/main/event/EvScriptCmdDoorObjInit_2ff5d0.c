/* rgp:protos */
#define RGP_SELF_EvScriptCmdDoorObjInit_2ff5d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004E69D0[];
extern void *D_00482850;
extern void *D_00482858;
extern void *D_00482860;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


s32 EvScriptCmdDoorObjInit_2ff5d0(u8 *p, s32 argc)
{
    EvScriptTemplatesReset_301c20();
    if (argc != 3 && argc != 4) {
        return 0;
    }
    D_00482850 = EventScratchAlloc_301b00(0x80);
    D_00482858 = EventScratchAlloc_301b00(0xC00);
    D_00482860 = EventScratchAlloc_301b00(0x300);
    if (D_00482850 == 0 || D_00482858 == 0 || D_00482860 == 0) {
        return 1;
    }
    switch (argc) {
    case 3:
        EvDoorObjInitByName_304380(D_004E69D0, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0, 0,
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     D_00482850, 0, D_00482860, 0);
        break;
    case 4:
        EvDoorObjInitByName_304380(D_004E69D0, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x18)),
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     D_00482850, 0, D_00482860, 0);
        break;
    }
    return 1;
}
