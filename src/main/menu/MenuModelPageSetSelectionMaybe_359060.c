#include "types.h"

typedef struct {
    u8 pad0[0xDA];
    s16 tbl[8];
    u8 xEA;
    s8 xEB[8];
    s8 m[4][2][2];
    u8 pad103[0x10];
    s8 n[4][2][2];
    u8 pad123[0x4A];
    u8 x16D[8];
    u8 x175;
} A;

typedef struct {
    u8 pad0[0x14];
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
} B;

void MenuModelPageSetSelectionMaybe_359060(A *a, s32 arg1, s8 arg2, B *arg3) {
    s32 k;

    k = a->tbl[a->x175] - 0x2AF9;
    a->xEA = a->tbl[arg1] - 0x2AF9;
    a->xEB[a->xEA] = arg2;
    if (arg3 != NULL) {
        a->m[k][a->x16D[a->x175]][0] = arg3->x14;
        a->m[k][a->x16D[a->x175]][1] = arg3->x16;
        a->n[k][a->x16D[a->x175]][0] = arg3->x18;
        a->n[k][a->x16D[a->x175]][1] = arg3->x1A;
    }
}
