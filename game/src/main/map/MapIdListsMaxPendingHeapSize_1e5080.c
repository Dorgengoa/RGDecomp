/* rgp:protos */
#define RGP_SELF_MapIdListsMaxPendingHeapSize_1e5080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapIdListsMaxPendingHeapSize_1e5080(s32 arg0)
{
    s32 var_16;
    s16 *var_19;
    s16 *var_19_2;
    s16 *var_19_3;
    s32 var_18;
    s32 var_18_2;
    s32 var_18_3;
    s32 temp_20;
    s32 temp_20_2;
    s32 temp_20_3;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    var_16 = 0;
    var_19 = ((s16 *)MapIdListGetEntries_1e5a70(arg0 + 0x20B0));
    temp_20 = MapIdListCount_1e5a40(arg0 + 0x20B0);
    var_18 = 0;
    while (var_18 < temp_20) {
        temp_2 = ((s32)MapFindAreaSlotById_1e4cb0(arg0, *var_19));
        if ((temp_2 != 0) && (((unsigned char)MapDataIsEnabled_1e7c20(temp_2)) != 0) && (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(temp_2)) == 0)) {
            var_16 = (MapDataGetHeapSize_1e7ba0(temp_2) < var_16) ? var_16 : MapDataGetHeapSize_1e7ba0(temp_2);
        }
        var_18 += 1;
        var_19 += 4;
    }
    var_19_2 = ((s16 *)MapIdListGetEntries_1e5a70(arg0 + 0x2154));
    temp_20_2 = MapIdListCount_1e5a40(arg0 + 0x2154);
    var_18_2 = 0;
    while (var_18_2 < temp_20_2) {
        temp_2_2 = MapSlotsFindShareById_1e4a50(arg0, *var_19_2, 0);
        if ((temp_2_2 != 0) && (((unsigned char)MapDataIsEnabled_1e7c20(temp_2_2)) != 0) && (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(temp_2_2)) == 0)) {
            var_16 = (MapDataGetHeapSize_1e7ba0(temp_2_2) < var_16) ? var_16 : MapDataGetHeapSize_1e7ba0(temp_2_2);
        }
        var_18_2 += 1;
        var_19_2 += 4;
    }
    var_19_3 = ((s16 *)MapIdListGetEntries_1e5a70(arg0 + 0x21F8));
    temp_20_3 = MapIdListCount_1e5a40(arg0 + 0x21F8);
    var_18_3 = 0;
    while (var_18_3 < temp_20_3) {
        temp_2_3 = MapSlotsFindBlockById_1e49b0(arg0, *var_19_3, 0);
        if ((temp_2_3 != 0) && (((unsigned char)MapDataIsEnabled_1e7c20(temp_2_3)) != 0) && (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(temp_2_3)) == 0)) {
            var_16 = (MapDataGetHeapSize_1e7ba0(temp_2_3) < var_16) ? var_16 : MapDataGetHeapSize_1e7ba0(temp_2_3);
        }
        var_18_3 += 1;
        var_19_3 += 4;
    }
    return var_16;
}
