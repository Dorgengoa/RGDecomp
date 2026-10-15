#include "types.h"

extern s32 StrEqualNoCase_1ca610(s32 arg0, s32 arg1);
extern s32 EventScriptRecGetEntries_2e3890(s32 arg0);
extern s32 EventScriptRecGetEntryCount_2e38a0(s32 arg0);
extern s32 EvObjGetScriptList_2f9c80(void);
extern void ScriptCallWithArgs_302770(s32 arg0, s32 arg1, s32 arg2);
extern s32 ScriptCallGetArgStr_302940(s32 arg0, s32 arg1);
extern s32 ScriptCallGetArgc_302aa0(s32 arg0);

void EvScriptDispatchByName_2f9bb0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_18;
    s32 temp_2;
    s32 var_20;
    s32 var_19;

    if (arg1 != 0) {
        temp_2 = EvObjGetScriptList_2f9c80();
        if (temp_2 != 0) {
            var_20 = EventScriptRecGetEntries_2e3890(temp_2);
            temp_18 = EventScriptRecGetEntryCount_2e38a0(temp_2);
            var_19 = 0;
            while (var_19 < temp_18) {
                if ((ScriptCallGetArgc_302aa0(var_20) > 0) && (StrEqualNoCase_1ca610(ScriptCallGetArgStr_302940(var_20, 0), arg2) != 0)) {
                    ScriptCallWithArgs_302770(var_20, arg1, 1);
                }
                var_19 += 1;
                var_20 += 0xC;
            }
        }
    }
}
