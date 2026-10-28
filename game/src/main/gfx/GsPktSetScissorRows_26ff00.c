/* rgp:protos */
#define RGP_SELF_GsPktSetScissorRows_26ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GsPktSetScissorRows_26ff00(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_18;

    if (arg0 != 0) {
        temp_18 = DrawEnvGetWidth_1451e0(GetDrawCtx_15de80());
        GsPktOpenPrim_13f730(arg0, 6);
        GsPktWriteAD_13ec80(arg0, 0x40, ((s64)arg2<<48) | (((s64)(temp_18-1)<<16)|((s64)arg1<<32)));
        GsPktClose_13f5b0(arg0);
    }
}
