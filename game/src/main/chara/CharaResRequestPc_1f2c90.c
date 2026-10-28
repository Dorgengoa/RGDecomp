/* rgp:protos */
#define RGP_SELF_CharaResRequestPc_1f2c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                         /* extern */
/*rgp*/                    /* extern */
/*rgp*/    /* extern */
/*rgp*/                              /* extern */
/*rgp*/                                 /* extern */

s32 CharaResRequestPc_1f2c90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_22;
    s32 var_16;

    temp_22 = ((s32)GetCharaDataMgr_1fdb70());
    var_16 = PcDefGetCharaDataId_1f5060(arg3);
    if (arg3 == 0x2F11) {
        var_16 = 0x2B00;
    }
    if (var_16 == -1) {
        return 0;
    }
    if ((arg4 == 1) && (CharaDataFindById_1ed990(temp_22, var_16) == 0) && (CharaPcResRequest_1f1f40(arg0, arg2, arg3) == 0)) {
        return 0;
    }
    return CharaResRequest_1f2d90(arg0, arg1, arg2, (long long)(arg3), var_16, 0, 0);
    return 0;
}
