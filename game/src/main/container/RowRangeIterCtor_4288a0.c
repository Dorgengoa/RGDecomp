/* rgp:protos */
#define RGP_SELF_RowRangeIterCtor_4288a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_00472250[];
extern u8 D_0047CA10[];
extern u8 D_0047CAD0[];

void **RowRangeIterCtor_4288a0(void **arg0, void *arg1, int rgp_a2, int rgp_a3) {
    void *inner;
    void *temp;
    s32 val;

    *arg0 = D_00472250;
    *arg0 = D_0047CAD0;
    *arg0 = D_0047CA10;
    if (arg1 == NULL) {
        return arg0;
    }
    inner = *(void **)((u8 *)arg1 + 8);
    if (inner == NULL) {
        return arg0;
    }
    temp = *(void **)((u8 *)inner + 0x3C);
    val = *(s32 *)((u8 *)temp + 8);
    if (val == 0) {
        return arg0;
    }
    RowRangeIterInit_428750(arg0, val, (int)rgp_a2, (int)rgp_a3);
    return arg0;
}
