#include "types.h"

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
    u8 pad18[2];
    s16 unk1A;
} Item0034daa0;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} S0034daa0;

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 padA[0x4A - 0xA];
    char unk4A[0x20];
    char unk6A[0x10];
} Entry;

extern void Sprintf_1343b8(char *, const char *, ...);
extern void MemStackReset_14d830(s32);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern s32 LoaderRequestFile_1cd870(s32, char *, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern S0034daa0 *GetGameData_1fede0(void);
extern Item0034daa0 *UiEntryListFindByTag_28ea40(s32, s32);
extern u8 *UiFindWidget_290460(s32, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern char *strcat(char *, const char *);
extern char *strcpy(char *, const char *);
extern char D_00462950[];
extern s32 D_0047F6E4;
extern s16 D_0047F6EC;
extern s16 D_0047F6F0;
extern s32 D_00482338;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482E98;
extern Entry *D_00482E9C;

s32 HelpBoardLoadSelected_34daa0(void)
{
    char name[0x40];
    char name2[0x20];
    S0034daa0 *ctx;
    s32 i;
    s32 n;
    s32 h;
    u8 *p;

    MemStackReset_14d830(D_00482338);
    ctx = GetGameData_1fede0();
    {
        Item0034daa0 *it = UiEntryListFindByTag_28ea40(D_00482364, 0x1E);
        n = it->unk16 + it->unk1A;
    }
    for (i = 0; i < D_00482E98; i++) {
        if (StateFlagTest_3ccd70(ctx->unk10, D_00482E9C[i].unk6) == 0) {
            continue;
        }
        if (n <= 0) {
            D_0047F6EC = D_00482E9C[(u32)i].unk4;
            StateFlagSet_3ccb70(ctx->unk10, D_00482E9C[(u32)i].unk8, 1, 0);
            h = GetLoaderMgr_1f59d0();
            if (h == 0) {
                return 0;
            }
            strcpy(name, D_00462950);
            strcat(name, D_00482E9C[(s32)i].unk4A);
            Sprintf_1343b8(name, name, D_0047F6F0 - 1);
            Sprintf_1343b8(name2, D_00482E9C[(s32)i].unk6A, D_0047F6F0 - 1);
            D_0047F6E4 = LoaderRequestFile_1cd870(h, name, 0);
            if (D_0047F6E4 == -1) {
                return 0;
            }
            LoaderQueueAppendSeparator_1cd670(h);
            p = UiFindWidget_290460(D_00482360, 0x21C);
            if (p == 0) {
                return 0;
            }
            strcpy((char *)(p + 4), name2);
            return 1;
        } else {
            n--;
        }
    }
    return 1;
}
