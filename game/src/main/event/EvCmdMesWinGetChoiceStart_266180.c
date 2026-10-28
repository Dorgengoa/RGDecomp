/* rgp:protos */
#define RGP_SELF_EvCmdMesWinGetChoiceStart_266180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_00266180 {
    s32 a;
    s32 b;
} E8_FUN_00266180;

typedef struct R_FUN_00266180 {
    u8 pad000[0x1C40];
    void *m1C40;
} R_FUN_00266180;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinGetChoiceStart_266180(E8_FUN_00266180 *q)
{
    void *a;
    R_FUN_00266180 *r;

    a = ScriptGetInt_26a2a0(q++);
    r = ((R_FUN_00266180 *)MesMgrGetSlotWin_266af0(a));
    if (r == 0) return 0;
    ScriptSetRefInt_26a1e0(q, r->m1C40);
    return 1;
}
