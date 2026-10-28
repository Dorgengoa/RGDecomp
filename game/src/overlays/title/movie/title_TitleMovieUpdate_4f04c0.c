/* rgp:protos */
#define RGP_SELF_title_FUN_004f04c0_advance 1
#define RGP_SELF_title_TitleMovieUpdate_4f04c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F04C0 -- the per-frame step of the attract loop.
 * Two paths reach the same four-call "advance" block and retail emits it
 * TWICE, so it is a helper mwcc inlined at both sites, not a shared label.
 *
 * `bgezl` means the NEGATIVE case is the fall-through, so the `< 0` arm is
 * written first.
 */

extern s32 D_00480430;
extern s32 D_00484288;
extern void *D_00484290;
extern void *D_0048429C;

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

static inline s32 title_FUN_004f04c0_advance(void)
{
    MoviePlayerShutdown_1d56c0(D_00484290);
    MovieDrawFrame_1d5870(D_00484290);
    MovieFrameQueueSendNext_1d4b20();
    MemStackReset_14d830(D_0048429C);
    return 1;
}

s32 title_TitleMovieUpdate_4f04c0(void)
{
    D_00484288 = D_00484288 + 1;
    GetDrawCtx_15de80();
    GetDrawCtxNameTable_15de40();
    if (D_00480430 < 0) {
        if (MovieIsFinished_1d5680() != 0) {
            return title_FUN_004f04c0_advance();
        }
    } else {
        if (MovieIsFinished_1d5680() == 0) {
            if (MovieGetFrameCount_1d52d0() < D_00480430) {
                goto idle;
            }
        }
        return title_FUN_004f04c0_advance();
    }
idle:
    MoviePlayerWaitTick_1d5810(D_00484290);
    MovieDrawFrame_1d5870(D_00484290);
    MovieFrameQueueSendNext_1d4b20();
    if (D_00484288 == 1) {
        AudioDecSetInputVolumeF_1d52e0(1.0f);
    }
    return 0;
}
