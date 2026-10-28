extern "C" {
#include "types.h"

typedef struct {
    u8 pad0[6];
    u8 x6;
    u8 pad7[0x19];
    f32 r;
    f32 g;
    f32 b;
} C;

extern void ModelObjPlayMotionByName_1867a0(u8 *, u8 *, s32);
extern s32 *InsectColorRecGetEntry_391620(u8 *, s32);
extern void Sprintf_1343b8(u8 *, u8 *, s32);
extern C *ModelFindMaterialByName_391570(u8 *, u8 *);
extern u8 D_00464208[];
extern u8 D_00464210[];

#pragma opt_propagation off
#pragma opt_pulloutconstants off
void InsectModelApplyColorRec_3913f0(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 name[0x20] __attribute__((aligned(16)));
    s32 *t;
    s32 n;
    s32 i;
    C *o;
    u32 w;
    s32 r, g, b, a;
    f32 k;

    if (arg0 == NULL) {
        return;
    }
    ModelObjPlayMotionByName_1867a0(arg0, D_00464208, 4);
    t = InsectColorRecGetEntry_391620(arg1, arg2 - 1);
    if (t == NULL) {
        return;
    }
    n = t[0];
    if (n >= 3) {
        n = 3;
    }
    for (i = 0; i < n; i++) {
        Sprintf_1343b8(name, D_00464210, i);
        o = ModelFindMaterialByName_391570(arg0, name);
        if (o == NULL) {
            continue;
        }
        {
            f32 c[4] __attribute__((aligned(16))) = {0};
            w = t[i + 1];
            k = 255.0f;
            o->x6 = 1;
            g = (w >> 8) & 0xFF; b = (w >> 16) & 0xFF; a = (w >> 24) & 0xFF; r = w & 0xFF;
            c[0] = (f32)r / k; o->r = c[0];
            c[1] = (f32)g / k; o->g = c[1];
            c[2] = (f32)b / k; o->b = c[2];
            c[3] = (f32)a / k;
        }
    }
}

}
