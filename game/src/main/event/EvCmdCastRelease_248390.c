/* rgp:protos */
#define RGP_SELF_EvCmdCastRelease_248390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 { s32 m00; s32 m04; };

extern struct Obj0 * gEventContext;

s32 EvCmdCastRelease_248390(s32 p0)
{
    s32 t1;
    s32 r0;
    s32 t3;

    t1 = gEventContext->m04 + 0x60;
    r0 = ScriptGetInt_2490f0(p0);
    t3 = gEventContext->m00;
    EventCastRelease_24bf50(t1, t3, r0);
    DrawCtxVif1HandlerStop_15dc40();
    return 1;
}
