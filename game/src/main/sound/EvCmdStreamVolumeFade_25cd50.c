/* rgp:protos */
#define RGP_SELF_EvCmdStreamVolumeFade_25cd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_0025cd50;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdStreamVolumeFade_25cd50(T_0025cd50 *q)
{
    void *a;
    s32 b;
    f32 c;
    f32 d;

    a = GetLoaderMgr_1f59d0();
    b = ScriptGetInt_26a2a0(q++);
    c = TaggedGetFloat_26a280(q++);
    d = TaggedGetFloat_26a280(q);
    StreamSetChanVolumeFade_1cd960(a, b, (s32)d, c);
    return 1;
}
