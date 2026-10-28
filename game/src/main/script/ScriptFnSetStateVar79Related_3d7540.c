/* rgp:protos */
#define RGP_SELF_ScriptFnSetStateVar79Related_3d7540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnSetStateVar79Related_3d7540(s32 arg0)
{
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    StateVarSet_3cc9c0(*(s32 *)((u8 *)D_00483960 + 0x10), 0x79, 3, 1);
    VariantSetS32_36f040(arg0, 1, 1);
}
