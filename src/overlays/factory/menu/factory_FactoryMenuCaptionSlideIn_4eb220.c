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

extern void func_290F60(void *w, s32 a, s32 b, s32 c);
extern void func_290F50(void *w, s32 a, s32 b, s32 c, s32 d, f32 x);

void factory_FactoryMenuCaptionSlideIn_4eb220(void)
{
    void *w = D_004807E4;

    func_290F60(w, 0xC, -0xAA, 0);
    func_290F50(w, 0xC, 0, 0, 0, D_0047D248);
}
