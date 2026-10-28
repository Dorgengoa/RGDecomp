/* rgp:protos */
#define RGP_SELF_MenuObjGetFrontPos_386000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V_00386000;

/*rgp*/
/*rgp*/

void MenuObjGetFrontPos_386000(V_00386000 *out, void *src)
{
    V_00386000 a __attribute__((aligned(16)));
    V_00386000 b __attribute__((aligned(16)));
    V_00386000 c __attribute__((aligned(16)));

    *(u128 *)&b = *(u128 *)((s32)src + 0x180);
    MenuObjGetForwardVec_387140(src, &c, 2.0f);
    c.y = 0.0f;
    VecAdd_13be20(&a, &b, &c);
    a.y = a.y + 1.0f;
    *(u128 *)out = *(u128 *)&a;
}
