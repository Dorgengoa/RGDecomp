/* rgp:protos */
#define RGP_SELF_EvScriptCmdDoorObjSetFlags_2ff4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00451F00[];
extern u8 D_004E69D0[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdDoorObjSetFlags_2ff4b0(s32 a, s32 mode)
{
    void *x;
    void *y;

    if (mode != 1) return 0;
    x = ScriptArgGetStr_301a00((void *)a);
    y = ParseFlagNames_1ca700(x, D_00451F00, 0);
    EvObjSetFlags_2f9cb0(D_004E69D0, y);
    return 1;
}
