/* rgp:protos */
#define RGP_SELF_MenuYesNoCursorInput_377180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[0x400];
extern u8 D_004B27E0[0x400];

void MenuYesNoCursorInput_377180(s32 *arg0) {
    s32 v;

    if (GetPauseStep_2f6660() != 0) return;
    if (PadIsTriggered_1839f0(D_004B2570, 0x8000) || (((unsigned char)IsPad2Enabled_2882c0()) && PadIsTriggered_1839f0(D_004B27E0, 0x8000))) {
        v = *arg0;
        if (v > 0) {
            *arg0 = v - 1;
            PlayMenuSeThunk_289ef0(4);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) || (((unsigned char)IsPad2Enabled_2882c0()) && PadIsTriggered_1839f0(D_004B27E0, 0x2000))) {
        v = *arg0;
        if (v <= 0) {
            *arg0 = v + 1;
            PlayMenuSeThunk_289ef0(4);
        }
    }
}
