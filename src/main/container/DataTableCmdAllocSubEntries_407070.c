#include "types.h"

u8 VariantGetInt_15f780(s32 xa0, u8, u8 *);
s32 ArenaNew_407f50(s32, u8 *, s16, s32);
extern u8 *D_004830F8;
extern s16 D_004830FC;
extern u8 D_00483C78;
extern u8 D_00483C80;
extern u8 D_00483C84;

s32 DataTableCmdAllocSubEntries_407070(void) {
    s32 u_0;
    s32 n;
    s32 k;
    s32 cnt;
    s32 r;
    u8 *o;
    u8 *e6;
    u8 *e2;
    u8 *e17;

    o = D_004830F8;
    n = *(s16 *)(o + 0x7C);
    if (n <= 0) {
        return 1;
    }
    k = D_004830FC - 1;
    if (k >= n) {
        return 1;
    }
    e6 = *(u8 **)(o + 0x8C) + k * 8;
    if (D_00483C78 - 1 >= *(s16 *)(e6 + 0x2)) {
        return 1;
    }
    e2 = *(u8 **)(e6 + 0x4) + D_00483C78 * 0xC - 0xC;
    if (D_00483C80 - 1 >= (s32)*(u8 *)(e2 + 2)) {
        return 1;
    }
    e17 = *(u8 **)(e2 + 0x8) + D_00483C80 * 8 - 8;
    e17[1] = VariantGetInt_15f780(u_0, D_00483C80, e2);
    cnt = e17[1];
    if (cnt > 0) {
        r = ArenaNew_407f50(cnt * 2, o + 0x6C, *(s16 *)(o + 0x80), -1);
        *(s32 *)(e17 + 0x4) = r;
        if (r == 0) {
            return 1;
        }
    }
    D_00483C84 = 0;
    return 1;
}
