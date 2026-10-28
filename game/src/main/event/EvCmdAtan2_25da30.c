/* rgp:protos */
#define RGP_SELF_EvCmdAtan2_25da30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_0025da30;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdAtan2_25da30(T_0025da30 *q)
{
    f32 a;
    f32 b;
    f32 c;

    a = TaggedGetFloat_26a280(q++);
    b = TaggedGetFloat_26a280(q++);
    c = Atan2f_1291a8(a, b);
    ScriptSetRefFloat_26a1c0(q, c);
    return 1;
}
