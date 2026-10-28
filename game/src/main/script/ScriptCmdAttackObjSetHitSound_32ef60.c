/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjSetHitSound_32ef60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R32E {
    u8    pad000[0xA0];
    void *mOFF;
} R32E;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdAttackObjSetHitSound_32ef60(void *p, s32 mode)
{
    void *a;
    R32E *c;

    if (mode != 2) {
        return 0;
    }
    a = GetObjRefTable_313de0();
    c = ((R32E *)HandleRegistryLookup_314aa0(a, ScriptSlotGetInt_3348b0(p)));
    if (c == 0) {
        return 1;
    }
    c->mOFF = ScriptSlotGetInt_3348b0((u8 *)p + 8);
    return 1;
}
