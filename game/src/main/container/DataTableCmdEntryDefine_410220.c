/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_410220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s32 f004;
    u8  pad008[0x6];
    u8  b00E_0 : 1;
    u8  b00E_1 : 1;
    u8  b00E_2 : 1;
    u8  b00E_3 : 1;
    u8  b00E_4 : 1;
    u8  b00E_5 : 1;
    u8  b00E_6 : 1;
    u8  b00E_7 : 1;
    u8  pb00F_0 : 1;
    u8  b00F_1 : 1;
    u8  pb00F_2 : 6;
    u8  pad010[0x2C];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdEntryDefine_410220(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->b00E_0 = VariantGetInt_15f780(src++) != 0;
    e->b00E_1 = VariantGetInt_15f780(src++) != 0;
    e->b00E_2 = VariantGetInt_15f780(src++) != 0;
    e->b00E_3 = VariantGetInt_15f780(src++) != 0;
    VariantGetInt_15f780(src++);
    e->b00E_7 = VariantGetInt_15f780(src++) != 0;
    e->b00E_6 = VariantGetInt_15f780(src++) != 0;
    e->b00E_4 = VariantGetInt_15f780(src++) != 0;
    e->b00E_5 = VariantGetInt_15f780(src++) != 0;
    e->b00F_1 = VariantGetInt_15f780(src) != 0;
    D_004830FC = D_004830FC + 1;
    return 1;
}
