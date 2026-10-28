/* rgp:protos */
#define RGP_SELF_ScriptCmdObjPlaySound_32eb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdObjPlaySound_32eb00(void *a0, s32 mode)
{
    s32 v;
    s32 r;
    s32 rec;
    s32 t;
    f32 f;

    if (mode != 2 && mode != 3) {
        return 0;
    }
    v = GetCurrentScene_1f5be0();
    r = ScriptSlotGetInt_3348b0(a0);
    rec = ((s32)ObjRecGetLiveObject_1c4a90(v, r));
    if (rec == 0) {
        return 1;
    }
    f = 1.0f;
    if (mode > 2) {
        f = ScriptSlotGetFloat_334890((u8 *)a0 + 0x10);
    }
    t = *(s32 *)(rec + 0x4FC);
    SoundPlayScaledVolume_1b9520(t, ScriptSlotGetInt_3348b0((u8 *)a0 + 8), 0, f);
    return 1;
}
