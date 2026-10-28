/* rgp:protos */
#define RGP_SELF_EvCmdObjClothReset_25d090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00481F78;

s32 EvCmdObjClothReset_25d090(s64 * arg0, s32 arg1) {
    s32 var_18;
    s8 var_17;
    void *temp_2;

    temp_2 = ObjRecGetLiveObject_1c4a90(D_00481F78, ScriptGetInt_26a2a0((s32)arg0++));
    if (temp_2 == NULL) {
        return 1;
    }
    var_18 = 0x1E;
    var_17 = 0;
    if (arg1 >= 2) {
        var_18 = ScriptGetInt_26a2a0((s32)arg0++);
    }
    if (arg1 >= 3) {
        var_17 = ScriptGetInt_26a2a0((s32)arg0) != 0;
    }
    *(s32 *)((u8 *)temp_2 + 0x464) = var_18 + 1;
    *(s8 *)((u8 *)temp_2 + 0x468) = var_17;
    return 1;
}
