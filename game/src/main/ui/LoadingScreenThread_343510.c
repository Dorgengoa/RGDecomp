/* rgp:protos */
#define RGP_SELF_LoadingScreenThread_343510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00482D70;
extern s32 D_00482D74;
extern u8 D_004B2570[];

void LoadingScreenThread_343510(void)
{
    s32 temp_16;
    s32 temp_16_2;
    s32 var_18;
    s32 temp_17;

    var_18 = 0;
    temp_17 = GetDrawCtx_15de80();
    while (D_00482D70 != 0) {
        temp_16 = ((unsigned char)GetLoadingResReady_1f69c0()) & 0xFF;
        if ((temp_16 != 0) && (var_18 == 0)) {
            PadWaitReady_1849e0(D_004B2570);
        }
        var_18 = temp_16 & 0xFF;
        DrawListFrameBegin_1425d0(temp_17, 1);
        temp_16_2 = LoadingScreenFrame_3435d0();
        GfxEndFrame_141c20(temp_17, 1);
        if (temp_16_2 != 0) {
            break;
        }
    }
    Vif1HandlerStop_141bf0(temp_17);
    LoadingScreenFreeImages_344690();
    D_00482D74 = 1;
}
