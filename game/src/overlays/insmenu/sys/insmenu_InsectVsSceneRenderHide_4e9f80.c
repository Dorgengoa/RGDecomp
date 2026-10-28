/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSceneRenderHide_4e9f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004E9F80 -- same guard shape again; here the argument setup for
 * the first call fills the guard's delay slot, which is why the branch is the
 * likely form. */
extern u8 D_00484310;
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsSceneRenderHide_4e9f80(void)
{
    if (D_00484310 == 0) {
        return 0;
    }
    TaskSetRenderTasksEnabled_287b90(0);
    SceneOverlayModeOn_288340();
    return 1;
}
