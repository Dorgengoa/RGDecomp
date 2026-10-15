#include "types.h"

/* factory.bin overlay, 0x004EACD0 -- leave the blueprint view, two ways.
 *
 * ★ Guard polarity: retail FALLS THROUGH into the `arg != 0` block and branches
 * away to the other, so the source condition is `!= 0` and m2c's `== 0` reading
 * lays the two arms out the wrong way round.
 * ★ `D_00484A44` is re-loaded at every use in both arms because a call
 * separates each one -- the global is spelled out, not hoisted into a local
 * (`levers.d/factory-count-the-gp-loads.md`).
 * ★ `lui 0xBE00`/`0x3E00`/`0xBF80`/`0x3F80` + `mtc1` are how mwcc materialises
 * -0.125f / 0.125f / -1.0f / 1.0f -- float constants whose low half is zero.
 */

typedef struct Scene {
    u8    pad00[0x64];
    void *f64;
    void *f68;
    u8    pad6C[0xC];
    u8    f78;
} Scene;

extern void  *D_004807EC;                       /* _gp - 0x4984 */
extern Scene *D_00484A44;                       /* _gp - 0x72C  */
extern u8     D_00484A84;                       /* _gp - 0x6EC  */
extern u8     D_00484A94;                       /* _gp - 0x6DC  */

extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_28EA90(void *ctx, s32 id, s32 a);
extern void factory_FactoryMenuRowsSlideOut_4eb320(void);
extern void factory_FactoryMenuCursorBob_4f0f30(Scene *s, s32 a);

void factory_FactoryMenuQuitConfirmClose_4eacd0(s32 keep)
{
    func_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
    func_290690(D_00484A44->f64, 0x1A, 0.0f, -0.125f, -1.0f);
    func_290690(D_00484A44->f64, 0x1E, 1.0f, 0.125f, -1.0f);
    if (keep != 0) {
        D_00484A84 = 1;
        func_28EA90(D_00484A44->f68, 0x88B8, 0);
        D_00484A94 = 3;
        factory_FactoryMenuRowsSlideOut_4eb320();
        D_00484A44->f78 = 0;
        factory_FactoryMenuCursorBob_4f0f30(D_00484A44, 1);
    } else {
        D_00484A84 = 1;
        func_28EA90(D_00484A44->f68, 0x88B8, 0);
        D_00484A94 = 0;
        D_00484A44->f78 = 0;
        factory_FactoryMenuCursorBob_4f0f30(D_00484A44, 1);
        func_290690(D_00484A44->f64, 0x19, 1.0f, 0.125f, -1.0f);
    }
}
