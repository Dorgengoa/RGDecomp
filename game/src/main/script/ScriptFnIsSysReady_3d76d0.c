/* rgp:protos */
#define RGP_SELF_ScriptFnIsSysReady_3d76d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnIsSysReady_3d76d0(s32 p0)
{
    if (p0 != 0) {
        VariantSetS32_36f040(p0, 0, 1);
        if (D_00483960 != 0) {
            if (D_00483964 != 0) {
                if (D_00483968 != 0) {
                    goto ok;
                }
            }
        }
    }
    return;
ok:
    VariantSetS32_36f040(p0, 1, 1);
}
