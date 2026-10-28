/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjSetMaxHits_32ee60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_0032ee60 {
    s32 a;
    s32 b;
} E8_FUN_0032ee60;

typedef struct R_FUN_0032ee60 {
    u8 pad000[0xBC];
    s16 mBC;
} R_FUN_0032ee60;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAttackObjSetMaxHits_32ee60(E8_FUN_0032ee60 *q, s32 mode)
{
    void *a;
    R_FUN_0032ee60 *b;
    s32 t;

    if (mode != 2) return 0;
    a = GetObjRefTable_313de0();
    t = ScriptSlotGetInt_3348b0(q);
    b = ((R_FUN_0032ee60 *)HandleRegistryLookup_314aa0(a, t));
    if (b == 0) return 1;
    b->mBC = ScriptSlotGetInt_3348b0(q + 1);
    return 1;
}
