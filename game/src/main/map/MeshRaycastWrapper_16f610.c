/* rgp:protos */
#define RGP_SELF_MeshRaycastWrapper_16f610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S16F610 { s32 a; s32 b; s32 c; s32 d; };

/*rgp*/

int MeshRaycastWrapper_16f610(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    struct S16F610 s __attribute__((aligned(16)));

    s.a = p1;
    s.b = p0;
    s.c = 0;
    s.d = 0;
    return MeshRaycastTris_16f3c0(&s, p2, p3, p4, p5, p6);
}
