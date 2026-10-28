/* rgp:protos */
#define RGP_SELF_UiGetWidgetAbsPos_290fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct {
    u8 pad0[0x2];
    u16 unk2;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x4];
    s16 *unk20;
} T290fc0_var_2;

void * UiGetWidgetAbsPos_290fc0(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) { void * rgp_v0 = 0;
    T290fc0_var_2 *v;

    *arg3 = 0;
    *arg2 = 0;
    v = (rgp_v0 = UiFindWidget_290460(arg0, arg1));
    if (v != NULL) {
        while (v != NULL) {
        *arg2 += v->unk14;
        *arg3 += v->unk18;
        if (v->unk20 != NULL) {
            *arg2 += v->unk20[0];
            *arg3 += v->unk20[1];
        }
        v = (rgp_v0 = UiFindWidget_290460(arg0, v->unk2));
        }
    }
return rgp_v0; }
