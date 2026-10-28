/* rgp:protos */
#define RGP_SELF_EvScriptDispatchByNameAndId_2f9ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                        /* extern */
/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/                              /* extern */

void EvScriptDispatchByNameAndId_2f9ab0(s32 pd0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_16;
    s32 temp_2;
    s32 var_18;
    s32 var_17;

    if (arg1 != 0) {
        temp_2 = EvObjGetScriptList_2f9c80((void *)pd0);
        if (temp_2 != 0) {
            var_18 = EventScriptRecGetEntries_2e3890(temp_2);
            temp_16 = EventScriptRecGetEntryCount_2e38a0(temp_2);
            for (var_17 = 0; var_17 < temp_16; var_17++, var_18 += 0xC) {
                if ((ScriptCallGetArgc_302aa0(var_18) >= 2) && (arg3 == ScriptCallGetArgInt_3029d0(var_18, 1)) && (((unsigned char)StrEqualNoCase_1ca610(ScriptCallGetArgStr_302940(var_18, 0), arg2)) != 0)) {
                    ScriptCallWithArgs_302770(var_18, arg1, 2);
                }
            }
        }
    }
}
