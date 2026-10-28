/* rgp:protos */
#define RGP_SELF_ScriptCmdObjMotionNameIs_333310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32, s32);

s32 ScriptCmdObjMotionNameIs_333310(s64 *arg0, s32 arg1) { __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    if (arg1 != 3) {
        return 0;
    }
    arg0++;
    a = ScriptSlotGetInt_3348b0((void *)rgp_entry_arg0);
    b = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    c = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a));
    if (c == 0) return 0;
    d = ModelObjGetMotionName_1add90(c);
    if (d == 0 || b == 0) return 0;
    ScriptSlotStoreIntRef_3347f0((s32)arg0, strcmp(d, b) == 0);
    return 1;
}
