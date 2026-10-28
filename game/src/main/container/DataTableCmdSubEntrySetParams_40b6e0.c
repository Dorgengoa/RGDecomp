/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntrySetParams_40b6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xE];
    u8  pb00E_0 : 1;
    u8  b00E_1 : 1;
    u8  b00E_2 : 1;
    u8  pb00E_3 : 5;
    u8  pad00F[0x1];
    s16 f010;
    s16 f012;
    s16 f014;
    s16 f016;
    s16 f018;
    s16 f01A;
    u8  pad01C[0xC];
} Ent;

typedef struct Lvl1 {
    u8  pad000[0x12];
    s16 cnt012;
    Ent *slots014;
} Lvl1;
typedef struct Lvl0 {
    u8  pad000[0xE];
    s16 cnt00E;
    Lvl1 *slots010;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdSubEntrySetParams_40b6e0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Lvl1 *e1;
    s32   n2;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt00E;
    if (p->m094 - 1 >= n1) return 1;
    e1 = &e0->slots010[p->m094] - 1;
    n2 = e1->cnt012;
    if (p->m098 - 1 >= n2) return 1;
    e = &e1->slots014[p->m098] - 1;
    e->b00E_1 = VariantGetInt_15f780(src++) != 0;
    e->b00E_2 = VariantGetInt_15f780(src++) != 0;
    e->f010 = VariantGetInt_15f780(src++);
    e->f012 = VariantGetInt_15f780(src++);
    e->f014 = VariantGetInt_15f780(src++);
    e->f016 = VariantGetInt_15f780(src++);
    e->f018 = VariantGetInt_15f780(src++);
    e->f01A = VariantGetInt_15f780(src);
    return 1;
}
