/* rgp:protos */
#define RGP_SELF_AiCmdCharaSetPos_2c96d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct V16 { s32 a; s32 b; s32 c; s32 d; };

/*rgp*/
/*rgp*/

extern struct { s32 v; s32 pad[3]; } D_004DB92C;

s32 AiCmdCharaSetPos_2c96d0(s32 p0, s32 p1)
{
    struct V16 v __attribute__((aligned(16)));
    s32 t0;

    if (p1 != 3) {
        return 0;
    }
    t0 = D_004DB92C.v;
    if (t0 == 0) {
        return 0;
    }
    ScriptSlotsToVec4_2cc920(&v, p0);
    v.d = 0x3F800000;
    CharaSetPosVec_2387a0(D_004DB92C.v, &v);
    return 1;
}
