/* rgp:protos */
#define RGP_SELF_EventPathEvalXformByName_2e3d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EventPathEvalXformByName_2e3d20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_2;

    if (arg1 == 0) {
        return 0;
    }
    temp_2 = EventPathRecFindPathByName_2e4040(arg0, arg2);
    if (temp_2 != 0) {
        return ((unsigned char)EventPathEvalXform_2e3da0(arg0, arg1, temp_2, arg3, arg4));
    }
    return 0;
}
