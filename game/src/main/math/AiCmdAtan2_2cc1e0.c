/* rgp:protos */
#define RGP_SELF_AiCmdAtan2_2cc1e0 1
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

s32 AiCmdAtan2_2cc1e0(void *a0, s32 mode)
{
    struct Slot *p;
    f32 x;
    f32 y;

    p = (struct Slot *)a0;
    if (mode != 3) {
        return 0;
    }
    x = ScriptSlotGetFloat_2cc9a0(p++);
    y = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreFloatRef_2cc8e0(p, Atan2f_1291a8(x, y));
    return 1;
}
