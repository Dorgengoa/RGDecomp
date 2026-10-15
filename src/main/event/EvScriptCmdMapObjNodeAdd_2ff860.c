#include "types.h"
#pragma opt_dead_assignments off

extern s32 ScriptArgGetStr_301a00(s32);
extern s32 EventStrDup_301aa0(s32);
extern void EvMapObjNodeInitWithName_367470(s32, s32);
extern s32 D_00482870;
extern s32 D_00482874;

s32 EvScriptCmdMapObjNodeAdd_2ff860(s32 pad0, s32 arg1) {
    s32 slot;

    if (arg1 != 1) {
        return 0;
    }
    if ((D_00482870 == 0) || (D_00482874 >= 0x20)) return 1;
    slot = D_00482870 + D_00482874 * 0x150;
    EvMapObjNodeInitWithName_367470(slot, EventStrDup_301aa0(ScriptArgGetStr_301a00(pad0)));
    D_00482874 += 1;
    return 1;
}
