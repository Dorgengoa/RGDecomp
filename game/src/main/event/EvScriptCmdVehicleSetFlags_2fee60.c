/* rgp:protos */
#define RGP_SELF_EvScriptCmdVehicleSetFlags_2fee60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00451F00[];
extern u8 D_004E6EC0[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdVehicleSetFlags_2fee60(s32 a, s32 mode)
{
    void *x;
    void *y;

    if (mode != 1) return 0;
    x = ScriptArgGetStr_301a00((void *)a);
    y = ParseFlagNames_1ca700(x, D_00451F00, 0);
    EvObjSetFlags_2f9cb0(D_004E6EC0, y);
    return 1;
}
