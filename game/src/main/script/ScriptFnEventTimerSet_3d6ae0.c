/* rgp:protos */
#define RGP_SELF_ScriptFnEventTimerSet_3d6ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B078[4];
extern u8 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnEventTimerSet_3d6ae0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 t;
    f32 f;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 < 2) {
        return;
    }
    t = VariantGetS32_36fb30(arg3);
    f = 60.0f * VariantGetFloat_36f7a0(arg3 + 0x38);
    EventTimerSet_3c06f0(*(s32 *)(D_00483960 + 0x18), t, f * D_0045B078[0]);
    VariantSetS32_36f040(arg0, 1, 1);
}
