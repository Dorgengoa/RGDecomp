/* rgp:protos */
#define RGP_SELF_EvCmdVecScale_25dcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct VN { s32 m00; f32 m04; } VN;
typedef struct E8 { s32 a; VN *b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVecScale_25dcd0(E8 *p0, s32 p1)
{
    f32 w[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 f;

    switch (p1) {
    case 4:
        v[0] = p0[0].b->m04;
        v[1] = p0[1].b->m04;
        v[2] = p0[2].b->m04;
        v[3] = 1.0f;
        f = TaggedGetFloat_26a280(p0 + 3);
        break;
    case 7:
        ScriptArgsToVec4_26a220(v, p0 + 3);
        f = TaggedGetFloat_26a280(p0 + 6);
        break;
    default:
        return 0;
    }
    VecScale_13be00(w, v, f);
    ScriptSetRefFloat_26a1c0(p0++, w[0]);
    ScriptSetRefFloat_26a1c0(p0++, w[1]);
    ScriptSetRefFloat_26a1c0(p0, w[2]);
    return 1;
}
