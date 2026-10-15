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
extern const u8 D_004B2570;

extern s32 func_1839F0(void *a, s32 b);
extern void func_184250(void *a, s32 b);
extern void func_1843A0(void *a);
extern s32 func_184960(void *a);
extern void func_1D5B30(void *a);
extern void func_1D5B40(void *a);
extern s32 func_1D62A0(void);
extern void func_206F20(void);
extern void func_207A50(void);
extern void func_2F5AE0(void);
extern void func_2F5E90(s32 a, s32 b);
extern void func_39ECF0(s32 a);
extern s32 title_TitleIsRunning_4ec840(void);
extern void title_TitleDraw_4ec890(void);
extern void title_TitleUpdate_4ec910(void);

u8 title_TitleFrameStep_4f0b20(void)
{
    if (func_1D62A0() != 0) {
        if (D_00484298 == 0) {
            func_1D5B40(D_00484290);
            D_00484298 = 1;
        }
        func_39ECF0(0);
    } else {
        if (D_00484298 != 0) {
            func_1D5B30(D_00484290);
            D_00484298 = 0;
        }
        if (D_004842A4 == 0) {
            D_00480434 = 1;
        } else {
            if (D_00480434 != 0) {
                if (func_184960((void *)&D_004B2570) == 0) {
                    D_00480434 = 0;
                    if (D_00484294 != 1) {
                        func_1D5B40(D_00484290);
                    }
                }
            } else if (func_184960((void *)&D_004B2570) != 0 &&
                       func_1839F0((void *)&D_004B2570, 0x40) != 0) {
                if (D_00484294 != 1) {
                    func_1D5B30(D_00484290);
                }
                func_1843A0((void *)&D_004B2570);
                func_184250((void *)&D_004B2570, 0);
                D_00480434 = 1;
            }
        }
        if (D_00480434 != 0 || D_00484294 == 1) {
            func_206F20();
            func_207A50();
        }
        title_TitleUpdate_4ec910();
        title_TitleDraw_4ec890();
        if (D_00480434 == 0) {
            func_2F5AE0();
            func_2F5E90(0, 0);
        }
    }
    return !(title_TitleIsRunning_4ec840() != 0);
}
