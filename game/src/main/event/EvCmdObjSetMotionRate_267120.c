/* rgp:protos */
#define RGP_SELF_EvCmdObjSetMotionRate_267120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_00267120;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjSetMotionRate_267120(T_00267120 *q)
{
    void *a;
    void *b;
    f32 f;

    a = ScriptGetInt_26a2a0(q++);
    b = EventSceneGetObj_2676e0(a);
    if (b == 0) return 0;
    f = TaggedGetFloat_26a280(q);
    ModelObjSetMotionRate_1add50(b, 1, f);
    return 1;
}
