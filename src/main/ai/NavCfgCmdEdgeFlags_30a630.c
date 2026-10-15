#include "types.h"

extern void *D_0048296C __attribute__((section(".sdata")));
extern const u8 D_00452330[];

extern s32 NavGraphGetEdgeCount_310c00(void *h);
extern void *NavGraphGetEdge_310c20(void *h, s32 i);
extern void *ScriptArgGetStr_30aaf0(void *p);
extern void *ParseFlagNames_1ca700(void *a, const u8 *b, s32 c);
extern void NavEdgeSetFlags_311650(void *x, void *y);

s32 NavCfgCmdEdgeFlags_30a630(void *p, s32 mode)
{
    s32 n;
    void *x;

    if (mode != 1) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    n = NavGraphGetEdgeCount_310c00(D_0048296C);
    x = NavGraphGetEdge_310c20(D_0048296C, n - 1);
    if (x == 0) {
        return 1;
    }
    NavEdgeSetFlags_311650(x, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(p), D_00452330, 0));
    return 1;
}
