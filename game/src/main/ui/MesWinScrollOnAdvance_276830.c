/* rgp:protos */
#define RGP_SELF_MesWinScrollOnAdvance_276830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0045F208;

void MesWinScrollOnAdvance_276830(s32 arg0)
{
    if (((short)MesWinGetFrameType_272b20((void *)arg0)) == 9) {
        if (((short)MesWinGetPage_272230(arg0)) > 0 && *(s16 *)(((short)MesWinGetPage_272230(arg0)) * 2 - (-arg0) + 0x5A) == 3) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208 + 4));
        }
    } else {
        MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208 + 4));
    }
}
