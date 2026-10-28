/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_402b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    __extension__ unsigned short b000_0 : 5;
    unsigned short b000_5 : 8;
    unsigned short pb000_13 : 3;
    unsigned char  b002_0 : 4;
    unsigned char  b002_4 : 4;
    u8  pad003[0x1];
} __attribute__((aligned(2))) Ent;

typedef struct Lvl0 {
    u8  pad000[0x7C];
    __extension__ signed short pb07C_0 : 5;
    signed short b07C_5 : 5;
    signed short pb07C_10 : 6;
    u8  pad07E[0x6];
    Ent *slots084;
    u8  pad088[0x8];
} __attribute__((aligned(2))) Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x8];
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdSubEntryDefine_402b70(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    Ent *q1;
    s32   n1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    q1 = e0->slots084;
    if (q1 == 0) return 1;
    n1 = (s16)(s32)e0->b07C_5;
    if (n1 <= 0) return 1;
    if (p->m098 - 1 >= n1) return 1;
    e = &q1[p->m098];
    e->b000_0 = VariantGetInt_15f780(src++);
    e->b000_5 = 100;
    e->b002_0 = VariantGetInt_15f780(src++);
    e->b002_4 = VariantGetInt_15f780(src);
    p->m098 = p->m098 + 1;
    return 1;
}
