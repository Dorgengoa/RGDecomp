#include "types.h"

extern void *ActCfgGetCurTable_23ff20(void);
extern void *ScriptArgGetStr_23fba0(void *self);
extern u32   ParseFlagNames_1ca700(void *p, const char *s, s32 z);
extern void  ActDataOrAttrFlags_225b50(void *r, u64 v);
extern const char D_0044C000[];
extern const char D_0044C1F0[];

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
    hi = (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044C000, 0) << 32;
    ActDataOrAttrFlags_225b50(r, hi | (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(self), D_0044C1F0, 0));
    return 1;
}
