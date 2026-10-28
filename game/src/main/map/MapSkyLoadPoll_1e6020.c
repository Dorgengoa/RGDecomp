/* rgp:protos */
#define RGP_SELF_MapSkyLoadPoll_1e6020 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: length-wrong (90w vs retail 91w), close. */
#include "types.h"

void Sprintf_1343b8(void *, void *, s16);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
extern u8 D_0045B498[0x400];

void MapSkyLoadPoll_1e6020(u8 *arg0) {
    u8 sp50[0x20] __attribute__((aligned(16)));
    s32 temp_3;
    s32 temp_2;
    s64 var_3;
    u8 *temp_17;
    u8 *temp_2_2;

    if (((short)MapSkyGetState_1e6350((void *)arg0)) == 1) {
        LoadHandlePoll_1ccb00(arg0 + 0x17B0);
        temp_3 = *(s16 *)(arg0 + 0x17B2);
        if (temp_3 != 0) {
            if ((temp_3 == 1) && (*(s32 *)(arg0 + 0x17B4) != 0) && (*(s32 *)(arg0 + 0x17B8) > 0)) {
                temp_2 = MapSkyGetHeap_1e6330(arg0);
                if (temp_2 != 0) {
                    MemStackHeapReinit_14de90(temp_2);
                    MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40);
                    temp_17 = ((u8 *)GetDrawCtxNameTable_15de40());
                    Sprintf_1343b8(sp50, &(*(u16 *)D_0045B498), *(s16 *)(arg0 + 0x17C2));
                    strcpy((char *)(temp_17 + 0x1E4), (const char *)sp50);
                    MapSkyArchiveLoad_17e210(arg0, *(s32 *)(arg0 + 0x17B4), 0, temp_2);
                    temp_2_2 = ((u8 *)GetCurrentScene_1f5be0());
                    ObjRecTableBindSlot_1c3a90(temp_2_2, 0, arg0, 0);
                    *(s32 *)(temp_2_2 + 0x4380) = -1;
                    *(u8 *)(temp_17 + 0x1E4) = 0;
                    MemStackReturnToOwnerMaybe_14dad0(temp_2);
                    *(s16 *)(arg0 + 0x17C0) = *(s16 *)(arg0 + 0x17C2);
                    *(u16 *)(arg0 + 0x17C6) = 1;
                    Nop_1e99c0();
                    Nop_1e99c0();
                }
            }
            LoaderReleaseHandle_1ccb70(arg0 + 0x17B0);
            if (((unsigned char)MapSkyIsLoaded_1e6340(arg0)) != 0) {
                var_3 = 2;
            } else {
                var_3 = -1;
            }
            *(s16 *)(arg0 + 0x17C4) = ((s64) (var_3 << 0x38) >> 0x38);
        }
    }
}
