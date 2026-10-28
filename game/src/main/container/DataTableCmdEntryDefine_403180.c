/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_403180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct S14 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} S14;

typedef struct Ent {
    s16 f000;
    u8  pad002[0xE];
    s16 f010;
    u8  pad012[0x2];
    s32 f014;
    s16 f018;
    s16 f01A;
    s16 f01C;
    s16 f01E;
    f32 f020;
    s16 f024;
    s16 f026[3];
    u8  pad02C[0x14];
    S14 f040[3];
    u8  pad07C[0x2];
    s8  b07E_0 : 1;
    s8  b07E_1 : 1;
    s8  b07E_2 : 1;
    s8  b07E_3 : 1;
    u8  pad07F[0x11];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern f32   D_0045B080[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryDefine_403180(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    S14 *q;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f014 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f010 = VariantGetInt_15f780(src++);
    e->f018 = VariantGetInt_15f780(src++);
    e->f01A = VariantGetInt_15f780(src++);
    e->f01C = VariantGetInt_15f780(src++);
    e->f01E = VariantGetInt_15f780(src++);
    { f32 t_ = VariantGetFloat_15f740(src++); e->f020 = t_ * D_0045B080[0]; }
    e->f024 = VariantGetInt_15f780(src++);
    for (i = 0; i < 3; i++) {
        e->f026[i] = VariantGetInt_15f780(src++);
    }
    q = e->f040;
    for (i = 0; i < 3; i++, q++) {
        q->f4 = 0;
        q->f8 = 0;
        q->fC = 0;
        q->f10 = 0;
    }
    e->b07E_0 = (s8)VariantGetInt_15f780(src++);
    e->b07E_1 = (s8)VariantGetInt_15f780(src++);
    e->b07E_2 = (s8)VariantGetInt_15f780(src++);
    e->b07E_3 = (s8)VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
