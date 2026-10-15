#include "types.h"

extern void FactoryCompletionUpdate_3e7ae0(void *arg0);
extern void ShopListBuild_3e7e30(void *arg0);
extern void ShopStockUpdateByProgress_3e80d0(void *arg0);
extern void RankingUpdateMaybe_3e8ce0(void *arg0);
extern void HunterBountyUpdateAll_3e9050(void *arg0);
extern void RevelationBoardRefreshMaybe_3eaec0(void *arg0, s32 arg1, s32 arg2);

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
        HunterBountyUpdateAll_3e9050(arg0);
        RankingUpdateMaybe_3e8ce0(arg0);
    }
    if (*temp_16 == 7) {
        FactoryCompletionUpdate_3e7ae0(arg0);
    }
    if (*temp_16 == 8) {
        ShopStockUpdateByProgress_3e80d0(arg0);
        ShopListBuild_3e7e30(arg0);
        RevelationBoardRefreshMaybe_3eaec0(arg0, -1, 0);
    }
    return 1;
}
