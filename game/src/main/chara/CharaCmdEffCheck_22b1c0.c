/* rgp:protos */
#define RGP_SELF_CharaCmdEffCheck_22b1c0 1
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

s32 CharaCmdEffCheck_22b1c0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;
    s32 temp_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    temp_16=((s32)GetEffectMgr_2d9040());
    return CharaCmdRunIfElseEvnt_22e480(*arg0,EffectIsLoadedByName_2dff60(temp_16,ScriptArgGetStr_302cb0(arg1)),(u8 *)arg1+5,arg2-1);
}
