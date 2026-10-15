#include "types.h"
#pragma no_branch_likely on

s32 ListBubbleSortByKey_407a40(s32);
s32 ListBubbleSortByKey_407cb0(u8 *);
s32 ListBubbleSortByValueDesc_407da0(u8 *);
s32 WorldSubsysSortRecNop_407f20(u8 *);

s32 WorldSubsysSortLists_406e20(u8 *arg0, s32 arg1) {
    s32 n;
    u8 *p;
    s32 i;
    s32 m;
    u8 *q;
    s32 j;
    s32 c;
    s32 r;
    s32 k;

    if (arg1 == 0) {
        return 0;
    }
    n = *(s16 *)(arg0 + 0x7C);
    p = *(u8 **)(arg0 + 0x8C);
    for (i = 0; i < n; i++, p += 8) {
        WorldSubsysSortRecNop_407f20(p);
        m = *(s16 *)(p + 2);
        q = *(u8 **)(p + 4);
        for (j = 0; j < m; j++, q += 0xC) {
            ListBubbleSortByValueDesc_407da0(q);
            ListBubbleSortByKey_407cb0(q);
            c = *(u8 *)(q + 2);
            r = *(s32 *)(q + 8);
            for (k = 0; k < c; k++, r += 8) {
                ListBubbleSortByKey_407a40(r);
            }
        }
    }
    return 1;
}
