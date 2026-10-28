/* rgp:protos */
#define RGP_SELF_CharaAbilityDataRecreate_1f0840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaAbilityDataRecreate_1f0840(s32 arg0, s32 arg1)
{
    s32 buf[10] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_2;
    s32 i;

    if (((unsigned char)IsPcCharaId_1f52d0(arg1)) == 0) {
        return 0;
    }
    temp_16 = ((s32)GetCharaDataMgr_1fdb70());
    temp_2 = PcDefGetCharaDataId_1f5060(arg1);
    buf[0] = -1;
    buf[1] = -1;
    i = 0;
    do {
        buf[i + 2] = -1;
        i++;
    } while (i < 7);
    buf[0] = temp_2 - 0x3D1;
    buf[1] = 1;
    buf[9] = 0x3700;
    buf[6] = 0x3698;
    CharaDataReleaseById_1ed850(temp_16, buf[0]);
    return CharaDataCreate_1edab0(temp_16, buf) != 0;
}
