#include "types.h"

typedef struct {
    u16 f0 : 6;
    u16 f6 : 3;
    u16 f9 : 4;
    u16 f13 : 3;
} Key;

u8 *RevelationBoardCellGetEntry_3eae10(s32, s32, Key *);
u8 *RevelationBoardFindById_3eb580(void);

s32 RevelationBoardCellGetItemRec_3ead00(s32 arg0, s32 arg1, Key *arg2) {
    u8 *a;
    u8 *b;
    s32 idx;

    a = RevelationBoardFindById_3eb580();
    if (a == NULL) {
        return 0;
    }
    b = RevelationBoardCellGetEntry_3eae10(arg0, arg1, arg2);
    if (b == NULL) {
        return 0;
    }
    if (arg2->f9 < 10) {
        return 0;
    }
    idx = (u16)(s32)arg2->f6;
    if (idx < 0 || idx >= *(s16 *)(b + 0xC)) {
        return 0;
    }
    return *(s32 *)(*(u8 **)(a + 0x10) + *(s16 *)(*(u8 **)(b + 0x10) + idx * 4 + 2) * 4);
}
