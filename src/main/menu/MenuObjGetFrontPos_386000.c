#include "types.h"

typedef unsigned __int128 u128;
typedef struct { f32 x, y, z, w; } V_00386000;

extern void MenuObjGetForwardVec_387140(void *, V_00386000 *, f32);
extern void VecAdd_13be20(V_00386000 *, V_00386000 *, V_00386000 *);

void MenuObjGetFrontPos_386000(V_00386000 *out, void *src)
{
    V_00386000 a;
    V_00386000 b;
    V_00386000 c;

    *(u128 *)&b = *(u128 *)((s32)src + 0x180);
    MenuObjGetForwardVec_387140(src, &c, 2.0f);
    c.y = 0.0f;
    VecAdd_13be20(&a, &b, &c);
    a.y = a.y + 1.0f;
    *(u128 *)out = *(u128 *)&a;
}
