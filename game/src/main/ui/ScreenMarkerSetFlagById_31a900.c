/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetFlagById_31a900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ScreenMarkerSetFlagById_31a900(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 temp_2;

    if (arg2 == -1) {
        for (i = 0; i < 0x20; i++) {
            if ((s16)ScreenMarkerGetId_31c030(arg0, i) != -1) {
                ScreenMarkerSetFlag_31bf70(arg0, i, arg1 & 0xFF);
            }
        }
        return;
    }
    temp_2 = FindS16Index32_31be20((s32)arg0, arg2);
    if (temp_2 != -1) {
        ScreenMarkerSetFlag_31bf70(arg0, temp_2, arg1 & 0xFF);
    }
}
