/* rgp:protos */
#define RGP_SELF_CharaCmdDelEffect_22c120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdDelEffect_22c120(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;

    if ((arg2 != 0) && (arg2 != 1)) {
        return 0;
    }
    temp_16 = ((s32)GetEffectMgr_2d9040());
    switch (arg2) {
    case 0:
        EffectReleaseByKey_2e1260(temp_16, *arg0);
        break;
    case 1:
        EffectReleaseNodesByKey_2e1250(temp_16, *arg0, (void *)((s64) (s16) ScriptArgGetInt_302d70(arg1)));
        break;
    }
    return 1;
}
