/* rgp:protos */
#define RGP_SELF_EvCmdCastFindKey_2478b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx { u8 pad0[0x4]; u8 *f04; } Ctx;
typedef struct A A;

extern Ctx *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdCastFindKey_2478b0(A *a)
{
    void *p = gEventContext->f04 + 0x60;
    EventCastFindKeyByName_24bb50(p, ScriptGetCodeAddr_249050(a));
    return 1;
}
