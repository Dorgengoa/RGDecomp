/* rgp:protos */
#define RGP_SELF_CharaDataEnsureLoaded_1f0d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaDataEnsureLoaded_1f0d00(s32 arg0, s32 arg1) {
    s32 sp[10] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_2;
    s32 temp_5;
    s32 var_4;

    if (((unsigned char)IsPcCharaId_1f52d0(arg1)) == 0) {
        return 0;
    }
    temp_16 = ((s32)GetCharaDataMgr_1fdb70());
    temp_2 = PcDefGetCharaDataId_1f5060(arg1);
    if (CharaDataFindById_1ed990(temp_16, temp_2 - 0x3DD) != 0) {
        return 1;
    }
    var_4 = 0;
    sp[0] = -1;
    sp[1] = -1;
    do {
        sp[2 + var_4] = -1;
        var_4 += 1;
    } while (var_4 < 7);
    temp_5 = temp_2 - 0x3DD;
    sp[1] = 1;
    sp[0] = temp_5;
    sp[9] = 0x3900;
    sp[6] = 0x3898;
    CharaDataReleaseById_1ed850(temp_16, temp_5);
    return CharaDataCreate_1edab0(temp_16, &sp[0]) != 0;
}
