/* rgp:protos */
#define RGP_SELF_ActDataPrmt_23b6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_0044BB40[];
extern char D_0044BDA0[];

s32 ActDataPrmt_23b6b0(void *self, s32 k)
{
    void *r;
    u64   hi;

    if (k != 1) {
        return 0;
    }
    r = ActCfgGetCurTable_23ff20();
    if (r == 0) {
        return 1;
    }
    hi = (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044BB40, 0)) << 32;
    ActDataOrPrmtFlags_225b30(r, hi | (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044BDA0, 0)));
    return 1;
}
