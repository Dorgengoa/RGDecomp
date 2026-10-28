/* rgp:protos */
#define RGP_SELF_SeventhMysteryResPoll_395560 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (62w vs retail 64w). Guard chain rewritten as separate returns (lesson from EventPathTemplateAddPath_300b90) but still short 2 words. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00464280[0x400];
extern u8 D_004642A0[0x400];
extern s32 D_0047FF28;
extern s32 D_0047FF2C;
extern s32 D_0048346C;
extern s32 D_0048347C;
extern s8 D_00483484;
extern s16 D_0048348C;

s32 SeventhMysteryResPoll_395560(void) {
    s32 temp_2;
    s32 temp_17;
    s32 sp3C;
    s32 temp_16;

    temp_17 = ((s32)GetLoaderMgr_1f59d0());
    if (D_0047FF2C != 0) {
        return 1;
    }
    if (D_0047FF28 == -1) {
        return 1;
    }
    temp_2 = LoaderGetStatus_1cd4f0(temp_17, D_0047FF28);
    D_0047FF2C = temp_2;
    if (temp_2 == 1) {
        MemStackAlign64_14d8e0(D_0048346C);
        temp_16 = ((s32)LoaderGetData_1cd490(temp_17, D_0047FF28, &sp3C));
        ResGroupLoadByKind_42b840(((s32)GetMenuResGroup_206a40()), 2, 9, D_0048346C, temp_16);
        D_0048347C = MsgTableLoadFromArchive_202a50(temp_16, &(*(s32 *)D_00464280), D_0048346C);
        TexGroupLoadFromArchive_202be0(temp_16, &(*(s32 *)D_004642A0), D_0048346C, 0x32D, 0);
        D_00483484 = 1;
        LoaderReleaseById_1cd340(temp_17, D_0047FF28);
        D_0047FF28 = -1;
        D_0048348C = 1;
        return 1;
    }
    return 0;
}
