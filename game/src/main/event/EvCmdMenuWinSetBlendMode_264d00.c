/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetBlendMode_264d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MenuWinGet_2653e0 = "resolve the object id"; retail FALLS THROUGH the bnel into
   `$2 = 0; b epilogue`, so the source guard is `if (h == 0) return 0;`
   (same shape as the already-matching EvCmdMesWinSetParam_265f00). */

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetBlendMode_264d00(Cmd *p0)
{
    s32 id, v;
    void *h;

    id = ScriptGetInt_26a2a0((s32)p0++);
    v = ScriptGetInt_26a2a0((s32)p0);
    h = MenuWinGet_2653e0(id);
    if (h == 0) {
        return 0;
    }
    MenuWinSetBlendMode_26c270(h, v);
    return 1;
}
