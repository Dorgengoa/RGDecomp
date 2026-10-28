/* rgp:protos */
#define RGP_SELF_GameDataPurposeRefresh_3eb5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 GameDataPurposeRefresh_3eb5c0(void *arg0)
{
    s16 *temp_16;
    void *temp_2;

    temp_2 = *(void **)((u8 *)arg0 + 8);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_16 = *(s16 **)((u8 *)temp_2 + 0x28);
    if (temp_16 == NULL) {
        return 0;
    }
    if (*temp_16 == 1) {
        RevelationBoardRefreshMaybe_3eaec0(arg0, -1, 0);
    }
    if (*temp_16 == 2) {
        HunterBountyUpdateAll_3e9050(arg0, 0, 0, 0);
        RankingUpdateMaybe_3e8ce0(arg0);
    }
    if (*temp_16 == 7) {
        FactoryCompletionUpdate_3e7ae0(arg0, 0, 0, 0);
    }
    if (*temp_16 == 8) {
        ShopStockUpdateByProgress_3e80d0(arg0);
        ShopListBuild_3e7e30(arg0);
        RevelationBoardRefreshMaybe_3eaec0(arg0, -1, 0);
    }
    return 1;
}
