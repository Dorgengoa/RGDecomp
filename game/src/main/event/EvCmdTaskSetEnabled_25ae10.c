/* rgp:protos */
#define RGP_SELF_EvCmdTaskSetEnabled_25ae10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdTaskSetEnabled_25ae10(void *a0)
{
    void *q;
    s32 r1;
    s32 r2;

    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptGetInt_26a2a0(q);
    r2 = ScriptGetCodeAddr_26a200(a0);
    TaskSetEnabled_27c2a0(r1 != 0, r2);
    return 1;
}
