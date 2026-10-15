#include "types.h"
/* normal 0x0051BFE0 -- the shop model open/close pass.  Both handle slots are
 * pre-zeroed BEFORE func_201A70 (the two `daddu ..,$0,$0`), so the two
 * func_324530 calls are guarded on locals, not on the camera.
 * `addiu $5,$28,-0x910` takes the ADDRESS of D_00484860, which must therefore
 * stay inside small data (declared at or under 8 bytes).
 * The five stack ints are allocated in REVERSE declaration order, so `nfound`
 * (sp+0x4C) is declared first and the second func_2910A0 pair last. */

typedef struct Root { u8 pad00[0x18]; void *f18; } Root;
typedef struct Vw   { u8 pad00[0x30]; s16 f30; } Vw;
typedef struct Pl   { u8 pad000[0x510]; void *f510; void *f514; } Pl;

extern f32   D_0047D9D4;          /* gp - 0x779C */
extern f32   D_0047D9D8;          /* gp - 0x7798 */
extern f32   D_0047D9DC;          /* gp - 0x7794 */
extern s32   D_00484760;          /* gp - 0xA10  */
extern s32   D_00484764;          /* gp - 0xA0C  */
extern s32   D_00484768;          /* gp - 0xA08  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484860;          /* gp - 0x910  */
extern s32   D_00484884;          /* gp - 0x8EC  */

extern void *func_1E49B0(void *p, s16 n, s32 *out);
extern Root *func_1FEDE0(void);
extern Pl   *func_201A70(void);
extern void *func_201A90(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern void  func_2910A0(void *w, u16 id, s32 *outX, s32 *outY);
extern void  func_324530(void *a, void *b, s32 c, s32 d);
extern void  normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c);
extern void  normal_TransWarpCloseSlide_51c1e0(void);

s32 normal_TransWarpCloseState_51bfe0(void *a, s32 b)
{
    s32   n;
    s32   x;
    s32   y;
    s32   x2;
    s32   y2;
    Root *h;
    Pl   *pl;
    void *o2;
    void *o1;
    void *p2;

    if (b != 0) {
        func_290690(D_00484710, 0x75DC, 0.0f, D_0047D9D8, -1.0f);
        func_290690(D_00484710, 0x75DB, 0.0f, D_0047D9D8, -1.0f);
        func_290690(D_00484710, 0x75D0, 0.0f, D_0047D9D4, -1.0f);
        func_290690(D_00484710, 0x75D2, 0.0f, D_0047D9DC, -1.0f);
        func_290690(D_00484710, 0x75D3, 0.0f, D_0047D9DC, -1.0f);
        normal_TransMenuBobIconMoveTo_518420(D_00484760, D_00484764, D_00484768);
        h = func_1FEDE0();
        p2 = func_201A90();
        if (p2 != 0) {
            n = 0;
            func_1E49B0(p2, ((Vw *)h->f18)->f30, &n);
            if (n != 0) {
                o2 = 0;
                o1 = 0;
                pl = func_201A70();
                if (pl != 0) {
                    o1 = pl->f514;
                    o2 = pl->f510;
                }
                if (o2 != 0) {
                    func_324530(o2, &D_00484860, 0xF, 0);
                }
                if (o1 != 0) {
                    func_324530(o1, &D_00484860, 0xF, 0);
                }
            }
        }
    }
    normal_TransWarpCloseSlide_51c1e0();
    func_2910A0(D_00484710, 0x753C, &x, &y);
    if (x == -0x12) {
        if (y == 0x9C) {
            func_290F60(D_00484710, 0x753C, -0x4A, 0x75);
            func_290F60(D_00484710, 0x7537, -0x45, 0x79);
        }
    }
    if (D_00484884 == 4) {
        func_2910A0(D_00484710, 0x753C, &x2, &y2);
        if (x2 == -0x4A) {
            func_28EDE0(D_0048470C, 1, 0);
        }
    }
    return 1;
}
