#include "types.h"

extern void Sprintf_1343b8(void *, void *, void *, void *);
extern void LoadHandleRequestFile_1ccbb0(void *, void *);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern void MapAreaDataReset_1e8fe0(void);
extern s32 GetLoaderMgr_1f59d0(void);
extern void strcpy(void *, void *);
extern char D_0045B4C8[];
extern char D_0045B4D0[];
extern char D_0045B4D8[];
extern char D_0045B4E0[];
extern char D_0045B4E8[];

s32 MapAreaDataRequestFiles_1e8a70(u8 *arg0, void *arg1, u8 *arg2, s32 arg3)
{
    char path[0x80];
    char names[4][0x20];
    char tmp[0x80];
    s32 i;

    MapAreaDataReset_1e8fe0();
    if (arg1 == NULL || arg2 == NULL || arg3 == 0) {
        return 0;
    }
    *(s32 *)(arg0 + 0x16D4) = arg3;
    *(u8 **)(arg0 + 0x16D8) = arg2;
    Sprintf_1343b8(path, D_0045B4C8, arg1, arg2);
    strcpy(names[0], D_0045B4D0);
    strcpy(names[2], D_0045B4D8);
    strcpy(names[1], D_0045B4E0);
    strcpy(names[3], D_0045B4E8);
    i = 0;
    do {
        Sprintf_1343b8(tmp, D_0045B4C8, path, names[i]);
        LoadHandleRequestFile_1ccbb0(arg0 + i * 0xC, tmp);
        i++;
    } while (i < 4);
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    *(s16 *)(arg0 + 0x16CA) = 0xB;
    return 1;
}
