/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuCaptionSlideIn_4eb220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EB220 -- two calls into the same widget.
 *
 * ★ ONE gp load into a callee-saved register, not one per use
 * (factory-count-the-gp-loads): retail has `lw $16, -0x498C($28)` once and
 * `daddu $4, $16, $0` at both sites, so D_004807E4 is a NAMED LOCAL here.
 * _gp = 0x00485170, so -0x498C is 0x004807E4 and -0x7F28 is 0x0047D248.
 */

extern void *D_004807E4;
extern f32   D_0047D248;

/*rgp*/
/*rgp*/

void factory_FactoryMenuCaptionSlideIn_4eb220(void)
{
    void *w = D_004807E4;

    UiSetWidgetPos_290f60(w, 0xC, -0xAA, 0);
    UiMoveWidgetUniform_290f50(w, 0xC, 0, 0, D_0047D248, 0);
}
