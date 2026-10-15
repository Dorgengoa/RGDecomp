#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Node {
    u8  pad000[0x10];
    s32 m10;
} Node;

typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
} Pool;

extern Pool *D_004830F8;
extern s32  VariantGetInt_15f780(R8 *q);
extern void StateFlag2Set_3cc6d0(s32 a, s32 b, s32 c);

s32 WorldDataCmdSetStateFlags2_3b9030(R8 *a)
{
    Pool *p = D_004830F8;
    s32 n;
    s32 i;
    s32 x;

    if (!p->b2) return 1;
    n = VariantGetInt_15f780(a++);
    for (i = 0; i < n; i++) {
        x = VariantGetInt_15f780(a++);
        StateFlag2Set_3cc6d0(p->m94->m10, x, VariantGetInt_15f780(a++) != 0);
    }
    return 1;
}
