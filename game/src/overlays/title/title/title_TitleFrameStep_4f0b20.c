/* rgp:protos */
#define RGP_SELF_title_TitleFrameStep_4f0b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0B20 -- the title screen's per-frame tick.
 *
 * When the disc layer is busy (func_1D62A0) it parks the audio stream and runs
 * the busy hook; otherwise it services the pad, drives the two title updates
 * and, unless the confirm latch D_00480434 is set, advances the background.
 * Returns whether title_TitleIsRunning_4ec840 has finished.
 */

extern u8 D_00480434;
extern void *D_00484290;
extern s32 D_00484294;
extern u8 D_00484298;
extern u8 D_004842A4;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u32 title_TitleFrameStep_4f0b20(void)
{
    if (MovieIsReadStalled_1d62a0() != 0) {
        if (D_00484298 == 0) {
            MoviePause_1d5b40();
            D_00484298 = 1;
        }
        DiscStatusMessageDraw_39ecf0(0);
    } else {
        if (D_00484298 != 0) {
            MovieResume_1d5b30();
            D_00484298 = 0;
        }
        if (D_004842A4 == 0) {
            D_00480434 = 1;
        } else {
            if (D_00480434 != 0) {
                if (((unsigned char)PadIsAnalogMode_184960((void *)&D_004B2570)) == 0) {
                    D_00480434 = 0;
                    if (D_00484294 != 1) {
                        MoviePause_1d5b40();
                    }
                }
            } else if (((unsigned char)PadIsAnalogMode_184960((void *)&D_004B2570)) != 0 &&
                       PadIsTriggered_1839f0((void *)&D_004B2570, 0x40) != 0) {
                if (D_00484294 != 1) {
                    MovieResume_1d5b30();
                }
                PadUpdate_1843a0((void *)&D_004B2570);
                PadUpdateVibration_184250((void *)&D_004B2570, 0);
                D_00480434 = 1;
            }
        }
        if (D_00480434 != 0 || D_00484294 == 1) {
            StreamStep_206f20();
            SceneSoundUpdate_207a50();
        }
        title_TitleUpdate_4ec910();
        title_TitleDraw_4ec890();
        if (D_00480434 == 0) {
            TaskDrawPauseFilter_2f5ae0();
            PadLostMsgDrawMaybe_2f5e90(0, 0);
        }
    }
    return (u8)(!(title_TitleIsRunning_4ec840() != 0));
}
