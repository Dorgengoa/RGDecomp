/* rgp:protos */
#define RGP_SELF_CharaDataNodeBuildPoll_1ef600 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaDataNodeBuildPoll_1ef600(u8 *arg0, s32 arg1)
{
    s32 sp5C;
    s32 h;
    s32 res;

    res = 0;
    if (*(s32 *)(arg0 + 0xC) >= 0) {
        h = ((s32)GetLoaderMgr_1f59d0());
        res = ({ __typeof__(((s32)LoaderGetData_1cd490(h, *(s32 *)(arg0 + 0xC), &sp5C))) rgp_ao0 = ((s32)LoaderGetData_1cd490(h, *(s32 *)(arg0 + 0xC), &sp5C)); CharaDataNodeBuild_1eee10(arg0, rgp_ao0, sp5C, arg1); });
        if (res == 1) {
            LoaderReleaseById_1cd340(h, *(s32 *)(arg0 + 0xC));
            *(s32 *)(arg0 + 0xC) = -1;
            *(u8 *)(arg0 + 0x1E) = 3;
        } else if (res == -1) {
            LoaderReleaseById_1cd340(h, *(s32 *)(arg0 + 0xC));
            *(s32 *)(arg0 + 0xC) = -1;
            *(s8 *)(arg0 + 0x1E) = CharaDataNodeFailStatus_1ef9a0(*(s16 *)(arg0 + 8));
            CharaDataNodeLoadFailStub_1ef7a0();
        }
    }
    return res;
}
