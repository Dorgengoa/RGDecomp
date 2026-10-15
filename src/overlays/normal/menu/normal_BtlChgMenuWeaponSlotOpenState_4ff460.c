#include "types.h"
/* normal 0x004FF460 -- brings up the 0x3D/0x3E pair, re-anchors 0x3E from
 * func_2910A0's measured origin, then (guarded on the panel pointer) rebuilds
 * the 0x3F sub-widget and pushes 25 * the 0x55F9 record's 0x16 field into its
 * 0x20 bar.  Both paths run the 0x40 fade and clear D_004844B8; the 0x55FE
 * post is outside the `b` guard.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family.  The two
 * out-params sit at sp+0x28/sp+0x2C: locals are allocated from the TOP of the
 * frame downward in DECLARATION order, so `y` (0x2C) is declared FIRST.
 * `sll 2 / addu / sll 2 / addu` is a strength-reduced `* 25`.
 * Both `beqz .L004FF570` land on the SHARED tail and retail falls through into
 * the body, so they are NESTED ifs, not early returns.
 */

typedef struct Rec  { u8 pad000[0x16]; s16 f016; } Rec;
typedef struct Bar  { u8 pad000[0x2];  s16 f002; } Bar;
typedef struct Hold { u8 pad000[0x20]; Bar *f020; } Hold;

extern void *D_00481BBC;          /* gp - 0x35B4 */
extern void *D_00484498;          /* gp - 0xCD8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern s32   D_004844B8;          /* gp - 0xCB8  */
extern f32   D_0047D518;          /* gp - 0x7C58 */

extern void *func_28AA30(void *bank, s32 id);
extern Rec  *func_28EA40(void *p, s32 id);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern Hold *func_290460(void *w, u16 id);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_2910A0(void *w, u16 id, s32 *ox, s32 *oy);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_BtlChgMenuWeaponSlotOpenState_4ff460(void *a, s32 b)
{
    s32 y;
    s32 x;
    Rec *r;
    Hold *h;

    if (b != 0) {
        func_291110(D_0048449C, 0x3D, 1, 1);
        func_291110(D_0048449C, 0x3E, 1, 1);
        func_28F510(D_0048449C, 0x3E, func_28AA30(D_00481BBC, 0x54), 0);
        func_28F510(D_0048449C, 0x3E, func_28AA30(D_00481BBC, 0x55), 1);
        func_2910A0(D_0048449C, 0x2B, &x, &y);
        func_290F60(D_0048449C, 0x3E, x + 0x1B, y + 0x41);
        if (D_0048449C != NULL) {
            r = func_28EA40(D_004844A0, 0x55F9);
            func_290F60(D_0048449C, 0x3F, 7, 6);
            h = func_290460(D_0048449C, 0x3F);
            if (h != NULL) {
                if (h->f020 != NULL) {
                    h->f020->f002 = r->f016 * 25;
                }
            }
        }
        func_290690(D_0048449C, 0x40, 1.0f, D_0047D518, -1.0f);
        D_004844B8 = 0;
    }
    func_28EDE0(D_00484498, 0x55FE, 0);
    return 1;
}
