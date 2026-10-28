#include "types.h"
#include "vec.h"

extern "C" {
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
void MenuObjGetForwardVec_387140(u8 *, Vec4 *, f32);
void MenuObjGetMoveDirMaybe_386fe0(u8 *arg0, Vec4 *arg1, Vec4 *arg2);
}



void MenuObjGetMoveDirMaybe_386fe0(u8 *arg0, Vec4 *arg1, Vec4 *arg2)
{
    Vec4 pos __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 t __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    u8 *p;
    u8 *q;
    u8 *r;
    f32 f;
    s32 m;

    *(u128 *)arg1 = 0;
    if (*(u8 **)(arg0 + 0x968) == 0) {
        return;
    }
    pos = *(Vec4 *)(arg0 + 0x180);
    switch (*(s32 *)(arg0 + 0x9B0)) {
    case 0:
        MenuObjGetForwardVec_387140(arg0, &d, 1.0f);
        if (*(s32 *)(arg0 + 0x9B0) == 2) {
            goto same;
        }
        q = *(u8 **)(arg0 + 0x9C4);
        if ((bool)q != false) {
            p = q;
        } else {
            p = *(u8 **)(arg0 + 0x9C8);
            switch ((bool)p) {
            case false:
                p = 0;
            }
        }
        if (p == 0) {
same:
            *arg2 = **(Vec4 **)(arg0 + 0x968);
        } else {
            r = *(u8 **)(arg0 + 0x9C8);
            if ((bool)r != false) {
                *arg2 = *(Vec4 *)(r + 0x180);
            } else if ((bool)(u32)q != false) {
                *arg2 = *(Vec4 *)(q + 0x180);
            }
        }
        if (*(s8 *)(arg0 + 0x984) == 0) {
            arg2->y = pos.y;
        }
        t = *arg2;
        f = *(f32 *)(arg0 + 0x9C0);
        VecSub_13be40(&a, &t, &pos);
        VecNormalize_13bd90(&b, &a);
        VecAdd_13be20(&c, &b, &d);
        VecNormalize_13bd90(&b, &c);
        VecScale_13be00(arg1, &b, f);
        break;
    case 1:
        *arg2 = pos;
        break;
    }
}
