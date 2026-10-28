/* rgp:protos */
#define RGP_SELF_ActDataAttr_23b860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_0044C000[];
extern char D_0044C1F0[];

s32 ActDataAttr_23b860(void *self, s32 k)
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
    hi = (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044C000, 0)) << 32;
    ActDataOrAttrFlags_225b50(r, hi | (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044C1F0, 0)));
    return 1;
}
