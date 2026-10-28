/* rgp:protos */
#define RGP_SELF_EvCmdObjGetPos_2674f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;

typedef struct T {
    u8 pad0000[0x180];
    V4 m180;
} T;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjGetPos_2674f0(R8 *q)
{
    T *r;
    V4 v __attribute__((aligned(16)));

    r = ((T *)EventSceneGetObj_2676e0(ScriptGetInt_26a2a0(q++)));
    if (r == 0) {
        return 0;
    }
    v = r->m180;
    ScriptSetRefFloat_26a1c0(q++, v.x);
    ScriptSetRefFloat_26a1c0(q++, v.y);
    ScriptSetRefFloat_26a1c0(q++, v.z);
    return 1;
}
