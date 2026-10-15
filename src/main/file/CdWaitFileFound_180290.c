#include "types.h"
extern void DelayThread_117618(s32);
extern s32 sceCdLayerSearchFile_1297e0(void *, s8 *, s32);
extern s32 sceCdSearchFile_129ae0(void *, s8 *);
extern void CdDiskReadyNewMaybe_12a508(s32);
extern s32 sceCdGetError_12aa98(void);
extern void sceCdTrayReq_12ae98(s32, s32 *);
extern s32 D_004811DC;
extern s32 D_004811E0;
extern s32 D_00481210;
extern s8 D_0049B6D0[0x40];

s32 CdWaitFileFound_180290(void)
{
    s32 sp3C;
    u8 sp10[0x2C];
    s32 r;
    s32 t;

    D_00481210 = 1;
    CdDiskReadyNewMaybe_12a508(0);
    for (;;) {
        if (D_0049B6D0[0] == 0) {
            break;
        }
        while (((t = D_004811DC) == 0 ? sceCdSearchFile_129ae0(sp10, D_0049B6D0) : sceCdLayerSearchFile_1297e0(sp10, D_0049B6D0, t == 0 ? 0 : D_004811E0)) == 0) {
            DelayThread_117618(0x2710);
        }
        if (sceCdGetError_12aa98() == 0) {
            break;
        }
        D_00481210 = 2;
        DelayThread_117618(0x2710);
    }
    sp3C = 0;
    sceCdTrayReq_12ae98(2, &sp3C);
    D_00481210 = 0;
    return 0;
}
