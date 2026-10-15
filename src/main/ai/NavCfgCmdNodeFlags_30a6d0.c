#include "types.h"

extern void *D_0048296C __attribute__((section(".sdata")));
extern const u8 D_00452300[];

extern s32 NavGraphGetNodeCount_310cb0(void *h);
extern void *NavGraphGetNode_310cd0(void *h, s32 i);
extern void *ScriptArgGetStr_30aaf0(void *p);
extern void *ParseFlagNames_1ca700(void *a, const u8 *b, s32 c);
extern void NavNodeSetFlags_3118a0(void *x, void *y);

s32 NavCfgCmdNodeFlags_30a6d0(void *p, s32 mode)
{
    s32 n;
    void *x;

    if (mode != 1) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    n = NavGraphGetNodeCount_310cb0(D_0048296C);
    x = NavGraphGetNode_310cd0(D_0048296C, n - 1);
    if (x == 0) {
        return 1;
    }
    NavNodeSetFlags_3118a0(x, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(p), D_00452300, 0));
    return 1;
}
