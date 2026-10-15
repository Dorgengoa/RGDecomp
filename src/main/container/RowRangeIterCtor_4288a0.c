#include "types.h"

extern void RowRangeIterInit_428750(void **, s32);
extern u8 D_00472250[];
extern u8 D_0047CA10[];
extern u8 D_0047CAD0[];

void **RowRangeIterCtor_4288a0(void **arg0, void *arg1) {
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
    RowRangeIterInit_428750(arg0, val);
    return arg0;
}
