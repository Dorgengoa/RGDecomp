#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Obj Obj;

typedef struct Node {
    u8  pad000[0x14];
    s32 m14;
} Node;

typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
    u8    pad09B[0x1];
    s16   m9C;
} Pool;

extern Pool *D_004830F8;
extern s32  VariantGetInt_15f780(R8 *q);
extern Obj *CharaMgrPoolFindById_3a8c60(s32 a, s16 b);
extern void CharaLearnAbility_3ad460(Obj *o, s32 v);

s32 WorldDataCmdCharaLearnAbilities_3b9720(R8 *a)
{
    Pool *p = D_004830F8;
    s16 t;
    Obj *o;
    s32 n;
    s32 i;

    if (!p->b2) return 1;
    t = p->m9C;
    if (t < 0) return 1;
    if ((o = CharaMgrPoolFindById_3a8c60(p->m94->m14, t)) == 0) return 1;
    n = VariantGetInt_15f780(a++);
    for (i = 0; i < n; i++) {
        CharaLearnAbility_3ad460(o, VariantGetInt_15f780(a++));
    }
    return 1;
}
