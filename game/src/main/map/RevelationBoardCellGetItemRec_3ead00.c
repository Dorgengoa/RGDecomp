/* rgp:protos */
#define RGP_SELF_RevelationBoardCellGetItemRec_3ead00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    __extension__ unsigned short f0 : 6;
    unsigned short f6 : 3;
    unsigned short f9 : 4;
    unsigned short f13 : 3;
} __attribute__((aligned(2))) Key;

/*rgp*/
/*rgp*/

s32 RevelationBoardCellGetItemRec_3ead00(s32 arg0, s32 arg1, Key *arg2, int rgp_a3) {
    u8 *a;
    u8 *b;
    s32 idx;

    a = ((u8 *)RevelationBoardFindById_3eb580((void *)arg0, (int)arg1, (int)arg2, (int)rgp_a3));
    if (a == NULL) {
        return 0;
    }
    b = ((u8 *)RevelationBoardCellGetEntry_3eae10(arg0, arg1, arg2, 0));
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
