/* rgp:protos */
#define RGP_SELF_EvCmdCastDetachRootFrame_2477d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

/*rgp*/
/*rgp*/
/*rgp*/

extern struct Obj0 * gEventContext;

s32 EvCmdCastDetachRootFrame_2477d0(s32 p0)
{
    s32 t1;
    s32 q;
    s32 r0;
    s32 r1;
    s32 r2;

    t1 = gEventContext->m04;
    q = t1 + 0x60;
    r0 = ScriptGetCodeAddr_249050(p0);
    r1 = EventCastFindKeyByName_24bb50(q, r0);
    r2 = (EventCastObjDetachRootFrame_24ab90(q, r1), (s32)0);
    return 1;
}
