/* rgp:protos */
#define RGP_SELF_NodeRefListAddAt_318d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };

extern f32 D_0047F220;
extern f32 D_0047F224;
extern f32 D_0047F228;
extern f32 D_0047F22C;

/*rgp*/

int NodeRefListAddAt_318d00(void *a, s32 b, s32 c, s32 d, s32 e, f32 x, f32 y, f32 z)
{
    struct Vec4 v __attribute__((aligned(16)));

    v.x = D_0047F220;
    v.y = D_0047F224;
    v.z = D_0047F228;
    v.w = D_0047F22C;
    v.x = x;
    v.y = y;
    v.z = z;
    return NodeRefListAdd_318d50(a, b, c, d, e, &v);
}
