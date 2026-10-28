/* rgp:protos */
#define RGP_SELF_MapAreaDataRequestFiles_1e8a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *, void *, void *, void *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(void *, void *);
extern char D_0045B4C8[];
extern char D_0045B4D0[];
extern char D_0045B4D8[];
extern char D_0045B4E0[];
extern char D_0045B4E8[];

s32 MapAreaDataRequestFiles_1e8a70(u8 *arg0, void *arg1, u8 *arg2, s32 arg3)
{
    char path[0x80] __attribute__((aligned(16)));
    char names[4][0x20] __attribute__((aligned(16)));
    char tmp[0x80] __attribute__((aligned(16)));
    s32 i;

    MapAreaDataReset_1e8fe0((void *)arg0, (int)arg1, (int)arg2, (int)arg3);
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
    LoaderQueueAppendSeparator_1cd670(((s32)GetLoaderMgr_1f59d0()));
    *(s16 *)(arg0 + 0x16CA) = 0xB;
    return 1;
}
