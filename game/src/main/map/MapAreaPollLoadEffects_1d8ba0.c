/* rgp:protos */
#define RGP_SELF_MapAreaPollLoadEffects_1d8ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapAreaPollLoadEffects_1d8ba0(void *arg0) {
    s32 temp_3;
    s32 temp_16;
    void *temp_2;

    LoadHandlePollThunk_1ccb00((u8 *)arg0 + 0xA8);
    temp_2 = MapAreaLoadHandleAt_1dd120((u8 *)arg0 + 0xA8, 0);
    if (temp_2 == NULL) {
        return -1;
    }
    temp_3 = *(s16 *)((u8 *)temp_2 + 2);
    if (temp_3 == 0) {
        return 0;
    }
    if (temp_3 == -1) {
        return 1;
    }
    if (*(s32 *)((u8 *)arg0 + 0x84) != 0) {
        MapAreaEffectsLoad_1e9100(*(s32 *)((u8 *)arg0 + 0x84), MapAreaGetGlobalIdMaybe_1dcee0(arg0), MapDataGetHeap_1e7850(arg0), *(s32 *)((u8 *)temp_2 + 4));
    }
    return 2;
}
