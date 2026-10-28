/* rgp:protos */
#define RGP_SELF_BattleCmdResLoadPoll_204e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045C1E8[0x400];
extern u8 D_0045C200[0x400];
extern s32 D_00481BB8;
extern s32 D_00481C20;
extern u8 D_00481C24;
extern u8 D_004BBC80[0x400];

s32 BattleCmdResLoadPoll_204e90(void)
{
    s32 sp3C;
    s32 temp_16;
    s32 temp_2;

    temp_16 = ((s32)GetLoaderMgr_1f59d0());
    if (D_00481C24 != 0) {
        return 0;
    }
    if (!(D_00481C20 > -1)) {
        return 0;
    }
    D_00481C24 = LoaderGetStatus_1cd4f0(temp_16, D_00481C20) != 0;
    if (D_00481C24 == 1) {
        sp3C = 0;
        temp_2 = ((s32)LoaderGetData_1cd490(temp_16, D_00481C20, &sp3C));
        D_00481BB8 = MsgTableLoadFromArchive_202a50(temp_2, &(*(u8 *)D_0045C200), &(*(u8 *)D_004BBC80));
        TexGroupLoadFromArchive_202be0(temp_2, &(*(u8 *)D_0045C1E8), &(*(u8 *)D_004BBC80), 0x32C, &(*(u8 *)D_004BBC80));
        LoaderReleaseById_1cd340(temp_16, D_00481C20);
        D_00481C20 = -2;
        return 1;
    }
    return 0;
}
