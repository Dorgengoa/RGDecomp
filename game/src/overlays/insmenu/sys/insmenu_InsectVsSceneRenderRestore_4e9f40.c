/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSceneRenderRestore_4e9f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004E9F40 -- same guard shape as insmenu_InsectVsTasksResume_4e9f00. */
extern u8 D_00484310;
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsSceneRenderRestore_4e9f40(void)
{
    if (D_00484310 == 0) {
        return 0;
    }
    SceneOverlayModeOff_288300();
    TaskSetRenderTasksEnabled_287b90(1);
    return 1;
}
