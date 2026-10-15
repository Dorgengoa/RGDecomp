#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern void GsPktSetRGBAQVec_13edd0(void *, s32);
extern void GsPktSetXYZVecI_13eeb0(void *, Vec *);
extern void GsPktClose_13f5b0(void *);
extern void GsPktOpenPrim_13f730(void *, s32);
extern s32 ProjectToScreen_15d340(Vec *, Vec *);
extern void MatMulPointXyz_1cb780(Vec *, s32, f32, f32, f32);
extern f32 D_004B3190[16];
extern f32 D_004B31D0[16];

void DrawWireSphere_1cc830(void *arg0, s32 arg1, s32 arg2)
{
    Vec e0;
    Vec d0;
    Vec c0;
    Vec b0;
    Vec a0;
    Vec v90;
    s32 i;
    s32 j;
    s32 k;

    GsPktOpenPrim_13f730(arg0, 1);
    GsPktSetRGBAQVec_13edd0(arg0, arg2);
    for (i = 1; i < 6; i++) {
        for (j = 0; j < 12; j++) {
            MatMulPointXyz_1cb780(&d0, arg1, D_004B3190[i] * D_004B3190[j], D_004B31D0[i], D_004B3190[i] * D_004B31D0[j]);
            MatMulPointXyz_1cb780(&e0, arg1, D_004B3190[i] * D_004B3190[j + 1], D_004B31D0[i], D_004B3190[i] * D_004B31D0[j + 1]);
            k = ProjectToScreen_15d340(&b0, &d0);
            if (k & ProjectToScreen_15d340(&c0, &e0)) {
                GsPktSetXYZVecI_13eeb0(arg0, &b0);
                GsPktSetXYZVecI_13eeb0(arg0, &c0);
            }
        }
    }
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 12; j++) {
            MatMulPointXyz_1cb780(&d0, arg1, D_004B3190[j] * D_004B3190[i], D_004B31D0[j], D_004B3190[j] * D_004B31D0[i]);
            MatMulPointXyz_1cb780(&e0, arg1, D_004B3190[j + 1] * D_004B3190[i], D_004B31D0[j + 1], D_004B3190[j + 1] * D_004B31D0[i]);
            k = ProjectToScreen_15d340(&v90, &d0);
            if (k & ProjectToScreen_15d340(&a0, &e0)) {
                GsPktSetXYZVecI_13eeb0(arg0, &v90);
                GsPktSetXYZVecI_13eeb0(arg0, &a0);
            }
        }
    }
    GsPktClose_13f5b0(arg0);
}
