#include "types.h"

extern void sceMcEndThunk_12c870(void *);
extern void *GetGameData_1fede0(void);
extern void GameDataReleaseWorld_3e53e0(void *);

extern void *D_004831D0;
extern s32 D_004831D4;
extern s32 D_004831D8;
extern s32 D_004831F8;
extern u8 D_004831F0;

void SaveMgrRelease_37bb70(void)
{
    void *p;

    if (D_004831D0 != 0) {
        sceMcEndThunk_12c870(D_004831D0);
    }
    p = GetGameData_1fede0();
    if (p != 0) {
        GameDataReleaseWorld_3e53e0(p);
    }
    D_004831D0 = 0;
    D_004831D4 = 0;
    D_004831D8 = 0;
    D_004831F8 = 0;
    D_004831F0 = 0;
}
