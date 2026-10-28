/* rgp:protos */
#define RGP_SELF_EvCmdCastAttachToFrame_247820 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_247820;
struct O247820 { u8 pad000[0x60]; u8 m60; };
struct C247820 { u8 pad000[0x4]; struct O247820 *m04; };
extern struct C247820 * gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCastAttachToFrame_247820(E8_247820 *p0)
{
    E8_247820 *q;
    s32 y1;
    s32 y2;
    u8 *base;
    s32 x3;

    q = p0;
    base = &gEventContext->m04->m60;
    y1 = EventCastFindKeyByName_24bb50(base, ScriptGetCodeAddr_249050(q++));
    y2 = EventCastFindKeyByName_24bb50(base, ScriptGetCodeAddr_249050(q++));
    x3 = ScriptGetCodeAddr_249050(q);
    EventCastAttachToFrame_24acd0(base, y1, y2, x3);
    return 1;
}
