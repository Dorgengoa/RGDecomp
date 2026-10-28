/* rgp:protos */
#define RGP_SELF_DrawWireCube_1cc1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Draws the twelve edges of a unit cube: eight corners are built with
   MatMulPointXyz_1cb780, then each edge is a pair of ProjectToScreen_15d340 results ANDed
   together (the AND is bitwise `&`, not `&&` -- retail keeps the first result
   in $16 and issues BOTH calls before `and $2, $16, $2`).

   The 32 Vec4 slots run 0x40..0x23F.  Stack slots go to the LAST-declared
   local first, so the declarations descend from 0x230 to 0x40. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void DrawWireCube_1cc1b0(s32 dev, s32 mtx, s32 colour)
{
    Vec4 h __attribute__((aligned(16)));
    Vec4 g __attribute__((aligned(16)));
    Vec4 f __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 e1b __attribute__((aligned(16)));
    Vec4 e1a __attribute__((aligned(16)));
    Vec4 e2b __attribute__((aligned(16)));
    Vec4 e2a __attribute__((aligned(16)));
    Vec4 e3b __attribute__((aligned(16)));
    Vec4 e3a __attribute__((aligned(16)));
    Vec4 e4b __attribute__((aligned(16)));
    Vec4 e4a __attribute__((aligned(16)));
    Vec4 e5b __attribute__((aligned(16)));
    Vec4 e5a __attribute__((aligned(16)));
    Vec4 e6b __attribute__((aligned(16)));
    Vec4 e6a __attribute__((aligned(16)));
    Vec4 e7b __attribute__((aligned(16)));
    Vec4 e7a __attribute__((aligned(16)));
    Vec4 e8b __attribute__((aligned(16)));
    Vec4 e8a __attribute__((aligned(16)));
    Vec4 e9b __attribute__((aligned(16)));
    Vec4 e9a __attribute__((aligned(16)));
    Vec4 e10b __attribute__((aligned(16)));
    Vec4 e10a __attribute__((aligned(16)));
    Vec4 e11b __attribute__((aligned(16)));
    Vec4 e11a __attribute__((aligned(16)));
    Vec4 e12b __attribute__((aligned(16)));
    Vec4 e12a __attribute__((aligned(16)));

    MatMulPointXyz_1cb780(&a, mtx, -1.0f, -1.0f, -1.0f);
    MatMulPointXyz_1cb780(&b, mtx, 1.0f, -1.0f, -1.0f);
    MatMulPointXyz_1cb780(&c, mtx, 1.0f, -1.0f, 1.0f);
    MatMulPointXyz_1cb780(&d, mtx, -1.0f, -1.0f, 1.0f);
    MatMulPointXyz_1cb780(&e, mtx, -1.0f, 1.0f, -1.0f);
    MatMulPointXyz_1cb780(&f, mtx, 1.0f, 1.0f, -1.0f);
    MatMulPointXyz_1cb780(&g, mtx, 1.0f, 1.0f, 1.0f);
    MatMulPointXyz_1cb780(&h, mtx, -1.0f, 1.0f, 1.0f);
    GsPktOpenPrim_13f730(dev, 1);
    GsPktSetRGBAQVec_13edd0(dev, colour);
    if (ProjectToScreen_15d340(&e1a, &a) & ProjectToScreen_15d340(&e1b, &b)) {
        GsPktSetXYZVecI_13eeb0(dev, &e1a);
        GsPktSetXYZVecI_13eeb0(dev, &e1b);
    }
    if (ProjectToScreen_15d340(&e2a, &b) & ProjectToScreen_15d340(&e2b, &c)) {
        GsPktSetXYZVecI_13eeb0(dev, &e2a);
        GsPktSetXYZVecI_13eeb0(dev, &e2b);
    }
    if (ProjectToScreen_15d340(&e3a, &c) & ProjectToScreen_15d340(&e3b, &d)) {
        GsPktSetXYZVecI_13eeb0(dev, &e3a);
        GsPktSetXYZVecI_13eeb0(dev, &e3b);
    }
    if (ProjectToScreen_15d340(&e4a, &d) & ProjectToScreen_15d340(&e4b, &a)) {
        GsPktSetXYZVecI_13eeb0(dev, &e4a);
        GsPktSetXYZVecI_13eeb0(dev, &e4b);
    }
    if (ProjectToScreen_15d340(&e5a, &e) & ProjectToScreen_15d340(&e5b, &f)) {
        GsPktSetXYZVecI_13eeb0(dev, &e5a);
        GsPktSetXYZVecI_13eeb0(dev, &e5b);
    }
    if (ProjectToScreen_15d340(&e6a, &f) & ProjectToScreen_15d340(&e6b, &g)) {
        GsPktSetXYZVecI_13eeb0(dev, &e6a);
        GsPktSetXYZVecI_13eeb0(dev, &e6b);
    }
    if (ProjectToScreen_15d340(&e7a, &g) & ProjectToScreen_15d340(&e7b, &h)) {
        GsPktSetXYZVecI_13eeb0(dev, &e7a);
        GsPktSetXYZVecI_13eeb0(dev, &e7b);
    }
    if (ProjectToScreen_15d340(&e8a, &h) & ProjectToScreen_15d340(&e8b, &e)) {
        GsPktSetXYZVecI_13eeb0(dev, &e8a);
        GsPktSetXYZVecI_13eeb0(dev, &e8b);
    }
    if (ProjectToScreen_15d340(&e9a, &a) & ProjectToScreen_15d340(&e9b, &e)) {
        GsPktSetXYZVecI_13eeb0(dev, &e9a);
        GsPktSetXYZVecI_13eeb0(dev, &e9b);
    }
    if (ProjectToScreen_15d340(&e10a, &b) & ProjectToScreen_15d340(&e10b, &f)) {
        GsPktSetXYZVecI_13eeb0(dev, &e10a);
        GsPktSetXYZVecI_13eeb0(dev, &e10b);
    }
    if (ProjectToScreen_15d340(&e11a, &c) & ProjectToScreen_15d340(&e11b, &g)) {
        GsPktSetXYZVecI_13eeb0(dev, &e11a);
        GsPktSetXYZVecI_13eeb0(dev, &e11b);
    }
    if (ProjectToScreen_15d340(&e12a, &d) & ProjectToScreen_15d340(&e12b, &h)) {
        GsPktSetXYZVecI_13eeb0(dev, &e12a);
        GsPktSetXYZVecI_13eeb0(dev, &e12b);
    }
    GsPktClose_13f5b0(dev);
}
