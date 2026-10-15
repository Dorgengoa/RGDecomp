#include "types.h"
#include "vec.h"

/* Draws the twelve edges of a unit cube: eight corners are built with
   MatMulPointXyz_1cb780, then each edge is a pair of ProjectToScreen_15d340 results ANDed
   together (the AND is bitwise `&`, not `&&` -- retail keeps the first result
   in $16 and issues BOTH calls before `and $2, $16, $2`).

   The 32 Vec4 slots run 0x40..0x23F.  Stack slots go to the LAST-declared
   local first, so the declarations descend from 0x230 to 0x40. */

extern void GsPktSetRGBAQVec_13edd0(s32, s32);
extern void GsPktSetXYZVecI_13eeb0(s32, Vec4 *);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern s32  ProjectToScreen_15d340(Vec4 *, Vec4 *);
extern void MatMulPointXyz_1cb780(Vec4 *, s32, f32, f32, f32);

void DrawWireCube_1cc1b0(s32 dev, s32 mtx, s32 colour)
{
    Vec4 h;
    Vec4 g;
    Vec4 f;
    Vec4 e;
    Vec4 d;
    Vec4 c;
    Vec4 b;
    Vec4 a;
    Vec4 e1b;
    Vec4 e1a;
    Vec4 e2b;
    Vec4 e2a;
    Vec4 e3b;
    Vec4 e3a;
    Vec4 e4b;
    Vec4 e4a;
    Vec4 e5b;
    Vec4 e5a;
    Vec4 e6b;
    Vec4 e6a;
    Vec4 e7b;
    Vec4 e7a;
    Vec4 e8b;
    Vec4 e8a;
    Vec4 e9b;
    Vec4 e9a;
    Vec4 e10b;
    Vec4 e10a;
    Vec4 e11b;
    Vec4 e11a;
    Vec4 e12b;
    Vec4 e12a;

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
