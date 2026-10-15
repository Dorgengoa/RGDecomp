#include "types.h"

s32 MemStackAlign64_14d8e0(s32);                                /* extern */
s32 LoaderReleaseById_1cd340(s32, s32);                           /* extern */
s32 LoaderGetData_1cd490(s32, s32, void *);                    /* extern */
s32 LoaderGetStatus_1cd4f0(s32, s32);                         /* extern */
s32 GetLoaderMgr_1f59d0();                                 /* extern */
s32 MsgTableLoadFromArchive_202a50(s32, void *, s32);                    /* extern */
s32 GetMenuResGroup_206a40();                                 /* extern */
s32 ResGroupLoadByKind_42b840(s32, s32, s32, s32, s32);                /* extern */
extern u8 D_00464470[0x400];
extern s32 D_0047FFD8;
extern s32 D_0047FFDC;
extern s32 D_00483688;
extern s32 D_0048369C;
extern s8 D_004836A4;
extern s16 D_004836AC;

s32 CompleteCheckResPoll_39eb80(void) {
    s32 temp_2;
    s32 r;
    s32 temp_17;
    s32 sp3C;
    s32 temp_16;

    temp_17 = GetLoaderMgr_1f59d0();
    if (D_0047FFDC != 0) {
        return 1;
    }
    if (D_0047FFD8 == -1) {
        return 1;
    }
    {
        D_0047FFDC = temp_2 = LoaderGetStatus_1cd4f0(temp_17, D_0047FFD8);
        if (temp_2 == 1) {
            MemStackAlign64_14d8e0(D_00483688);
            temp_16 = LoaderGetData_1cd490(temp_17, D_0047FFD8, &sp3C);
            ResGroupLoadByKind_42b840(GetMenuResGroup_206a40(), 2, 8, D_00483688, temp_16);
            D_0048369C = MsgTableLoadFromArchive_202a50(temp_16, &(*(s32 *)D_00464470), D_00483688);
            D_004836A4 = 1;
            LoaderReleaseById_1cd340(temp_17, D_0047FFD8);
            D_0047FFD8 = -1;
            D_004836AC = 1;
            return 1;
        }
        return 0;
    }
    return 1;
    return 1;
}
