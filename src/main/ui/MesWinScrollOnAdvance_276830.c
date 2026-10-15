#include "types.h"

extern void MesWinSetScrollTarget_2716e0(s32, s32);
extern s32 MesWinGetScrollY_271700(s32);
extern s32 MesWinGetPage_272230(s32);
extern s32 MesWinGetFrameType_272b20(void);
extern const s32 D_0045F208;

void MesWinScrollOnAdvance_276830(s32 arg0)
{
    if (MesWinGetFrameType_272b20() == 9) {
        if (MesWinGetPage_272230(arg0) > 0 && *(s16 *)(MesWinGetPage_272230(arg0) * 2 - (-arg0) + 0x5A) == 3) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208 + 4));
        }
    } else {
        MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208 + 4));
    }
}
