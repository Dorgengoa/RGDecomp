/* rgp:protos */
#define RGP_SELF_StatusEffectSlotDraw_33c580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct ObjFUN_0033c580 {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
} ObjFUN_0033c580;

void StatusEffectSlotDraw_33c580(ObjFUN_0033c580 *arg0, s32 arg1) {
    s16 temp_4;

    if (arg0->unk10 != 0) {
        temp_4 = arg0->unk12;
        if (temp_4 == 1 || temp_4 == 3) {
            DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg1, 1.0f);
            StatusEffectOrbitIconsDraw_33cb20(arg0);
            return;
        } else if (temp_4 == 10) {
            DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg1, 1.0f);
            StatusEffectHeadIconDraw_33cdf0(arg0);
            return;
        } else if (temp_4 == 5) {
            DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg1, 1.0f);
            StatusEffectHitIconsDraw_33c660(arg0);
        }
    }
}
