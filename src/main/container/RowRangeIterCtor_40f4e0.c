#include "types.h"

typedef struct {
    u8 pad[8];
    void *x8;
} B;

typedef struct {
    u8 pad[0x84];
    B *x84;
} P;

typedef struct {
    u8 pad[8];
    P *x8;
} A1;

extern void *GroupFindByKey_40eb80(B *, s16);
extern void RowRangeIterInit_40f360(void **, void *, s32, s32, s32, s32, s32);
extern u8 D_00472250[0x400];
extern u8 D_004794D0[0x400];
extern u8 D_00479650[0x400];

void **RowRangeIterCtor_40f4e0(void **arg0, A1 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    P *p;
    void *q;

    *arg0 = D_00472250;
    *arg0 = D_00479650;
    *arg0 = D_004794D0;
    if (arg1 == NULL) {
        return arg0;
    }
    p = arg1->x8;
    if (p == NULL) {
        return arg0;
    }
    if (arg2 < 0) {
        q = p->x84->x8;
    } else {
        q = GroupFindByKey_40eb80(p->x84, arg2);
    }
    if (q == NULL) {
        return arg0;
    }
    RowRangeIterInit_40f360(arg0, q, arg2, arg3, arg4, arg5, arg6);
    return arg0;
}
