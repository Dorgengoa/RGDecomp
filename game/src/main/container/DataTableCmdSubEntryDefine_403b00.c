/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_403b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    __extension__ unsigned short  b000_0 : 5;
    unsigned short b000_5 : 8;
    unsigned short pb000_13 : 3;
    unsigned char  b002_0 : 4;
    unsigned char  b002_4 : 4;
    u8  pad003[0x1];
} __attribute__((aligned(2))) Ent;

typedef struct Lvl0 {
    u8  pad000[0x2D];
    s8  cnt02D;
    u8  pad02E[0x6];
    Ent *slots034;
    u8  pad038[0x4];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0xC];
    s32  m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdSubEntryDefine_403b00(R8 *src)
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
    q1 = e0->slots034;
    if (q1 == 0) return 1;
    n1 = e0->cnt02D;
    if (n1 <= 0) return 1;
    if (p->m09C - 1 >= n1) return 1;
    e = &q1[p->m09C];
    e->b000_0 = VariantGetInt_15f780(src++);
    e->b000_5 = VariantGetInt_15f780(src++);
    e->b002_0 = VariantGetInt_15f780(src++);
    e->b002_4 = VariantGetInt_15f780(src);
    p->m09C = p->m09C + 1;
    return 1;
}
