/* rgp:protos */
#define RGP_SELF_title_TitleStateInit_4ec660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC660 -- straight-line init: two globals cleared,
 * three calls against the main-image object at 0x004B2570, one more call, then
 * eight stores that the scheduler interleaves into two alternating groups.
 */

extern s32 D_004803A0;
extern u8 D_004803A4;
extern s16 D_004803AC;
extern f32 D_004803B0;
extern f32 D_004803B4;
extern f32 D_0047D56C;
extern void *D_00484158;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern s16 D_00484194;
extern s16 D_00484198;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleStateInit_4ec660(void)
{
    D_004803A0 = -1;
    D_004803A4 = 0;
    PadClearRepeatAll_183960((void *)&D_004B2570);
    PadSetRepeat_183d50((void *)&D_004B2570, 0xF00C, 0xC, 7);
    PadSetStickDpadThreshold_183950((void *)&D_004B2570, 0x78);
    StateMachineSetState_28ede0(D_00484158, 2, 1);
    D_00484188 = 0;
    D_004803AC = 2;
    D_0048418C = 0;
    D_004803B0 = 1.0f;
    D_00484194 = 0;
    D_004803B4 = D_0047D56C;
    D_00484198 = 0;
    D_0048417C = 0;
    return 1;
}
