/* rgp:protos */
#define RGP_SELF_NodeRefListAddDefault_318df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };

extern f32 D_0047F210;
extern f32 D_0047F214;
extern f32 D_0047F218;
extern f32 D_0047F21C;

/*rgp*/

int NodeRefListAddDefault_318df0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    struct Vec4 v __attribute__((aligned(16)));

    v.x = D_0047F210;
    v.y = D_0047F214;
    v.z = D_0047F218;
    v.w = D_0047F21C;
    return NodeRefListAdd_318d50(a, b, c, d, e, &v);
}
