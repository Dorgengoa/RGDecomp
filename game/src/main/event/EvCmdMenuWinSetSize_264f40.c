/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetSize_264f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetSize_264f40(Cmd *p0)
{
    s32 id, a, b;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    a = ScriptGetInt_26a2a0((s32)p0++);
    b = ScriptGetInt_26a2a0((s32)p0);
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetSize_26c320(h, a, b);
    return 1;
}
