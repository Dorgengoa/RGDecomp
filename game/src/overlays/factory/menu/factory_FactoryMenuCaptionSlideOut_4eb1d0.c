/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuCaptionSlideOut_4eb1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EB1D0 -- park the shared window: move it off-screen
 * and start the slide-out timer.
 * 80 bytes, 20 instructions, 0 conditional branches, 2 calls.
 *
 * * `w = D_004807E4;` is a NAMED LOCAL, not the global spelled at both call
 * sites: retail has ONE `lw $16, -0x498C($28)` into a callee-saved register,
 * which is [[factory-count-the-gp-loads]]'s "one load" half.
 *
 * * `-0x498C` is `D_004807E4` and `-0x49EC` is `D_00480784`; the two names are
 * anagram-close, so recompute `_gp - offset` (`_gp` = 0x00485170).
 */

extern void *D_004807E4;                        /* _gp - 0x498C */
extern f32   D_0047D4F0;                        /* _gp - 0x7C80 */

/*rgp*/
/*rgp*/

void factory_FactoryMenuCaptionSlideOut_4eb1d0(void)
{
    void *w;

    w = D_004807E4;
    UiSetWidgetPos_290f60(w, 0xC, 0, 0);
    UiMoveWidgetUniform_290f50(w, 0xC, -0xAA, 0, D_0047D4F0, 0);
}
