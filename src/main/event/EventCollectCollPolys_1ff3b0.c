#include "types.h"

extern void *GetTreasureBoxPool_3389b0(void);
extern s32 TreasureBoxPoolCollectCollPolys_338af0(void *x, u8 *p, s32 n, void *c);
extern void *GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrCollectCollPolys_2e7bc0(void *y, u8 *p, s32 n, void *c, void *d);

s32 EventCollectCollPolys_1ff3b0(u8 *p, s32 n, void *c, void *d)
{
    s32 k;
    void *y;

    if (p == 0 || n <= 0) {
        return 0;
    }
    k = 0;
    k = k + TreasureBoxPoolCollectCollPolys_338af0(GetTreasureBoxPool_3389b0(), p, n, c);
    y = GetEventObjMgr_2d1960();
    return k + EventObjMgrCollectCollPolys_2e7bc0(y, p + k * 0x60, n - k, c, d);
}
