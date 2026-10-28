/* rgp:protos */
#define RGP_SELF_ScriptCmdAtan2_3342e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Slot {
    s32 a;
    s32 b;
};

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAtan2_3342e0(void *a0, s32 mode)
{
    struct Slot *p;
    f32 x;
    f32 y;

    p = (struct Slot *)a0;
    if (mode != 3) {
        return 0;
    }
    x = ScriptSlotGetFloat_334890(p++);
    y = ScriptSlotGetFloat_334890(p++);
    ScriptSlotStoreFloatRef_3347d0(p, Atan2f_1291a8(x, y));
    return 1;
}
