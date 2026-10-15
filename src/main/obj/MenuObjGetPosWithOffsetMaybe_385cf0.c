#include "types.h"

typedef unsigned __int128 u128;
typedef struct { f32 m[4]; } M_00385cf0;
typedef struct { f32 x, y, z, w; } V_00385cf0;

extern void MenuObjGetForwardVec_387140(void *, M_00385cf0 *, f32);
extern void ObjGetAttachNodePos_1adec0(void *, s32, V_00385cf0 *);
extern void VecAddInPlace_13e070(V_00385cf0 *, M_00385cf0 *);

void MenuObjGetPosWithOffsetMaybe_385cf0(void *p, V_00385cf0 *out, s32 mode)
{
    M_00385cf0 m;

    if (p == 0) return;
    MenuObjGetForwardVec_387140(p, &m, 2.0f);
    if (mode == 0) {
        *(u128 *)out = *(u128 *)((s32)p + 0x180);
    }
    if (mode == 1) {
        ObjGetAttachNodePos_1adec0(p, 0, out);
    }
    VecAddInPlace_13e070(out, &m);
}
