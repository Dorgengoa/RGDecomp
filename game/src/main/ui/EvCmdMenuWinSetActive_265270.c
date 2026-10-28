/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetActive_265270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetActive_265270(Cmd *p0, s32 n)
{
    /* h is declared BEFORE v: the earlier-declared local takes the HIGHER
       callee-saved register ($17) and v then shares $16 with id.  With
       `id, v` then `h` it is 5 bad words (a pure $16/$17 swap). */
    s32 id;
    void *h;
    s32 v;

    id = ScriptGetInt_26a2a0((s32)p0++);
    v = ScriptGetInt_26a2a0((s32)p0++);
    /* plain bnez on $2 with the handle copied in the delay slot =
       assignment-in-condition. */
    if ((h = MenuWinGet_2653e0(id)) == 0) {
        return 0;
    }
    MenuWinSetActive_26c3f0(h, v);
    if (n >= 3) {
        MenuWinSetDrawLayer_26c3d0(h, ScriptGetInt_26a2a0((s32)p0));
    }
    return 1;
}
