/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_428ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  b002_0 : 1;
    u8  b002_1 : 1;
    u8  b002_2 : 1;
    u8  pb002_3 : 5;
    u8  pad003[0x1];
    s16 f004;
    s16 f006;
    s16 f008;
    u8  pad00A[0x6];
    void *f010;
    u8  pad014[0xC];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdEntryDefine_428ea0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m;
    void *r;
    u8   buf[0x2000] __attribute__((aligned(16)));

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = i;
    m = Base64Decode_36a700(buf, SlotGetInt_15f720(src++));
    if (m > 2) {
        e->f008 = m - 2;
        r = ArenaAlloc_3702f0(p->m6C, (s16)(m - 2), 0x1);
        e->f010 = r;
        memcpy(r, buf + 2, e->f008);
    } else {
        e->f008 = 0;
        e->f010 = 0;
    }
    e->b002_0 = VariantGetInt_15f780(src++) != 0;
    e->b002_1 = VariantGetInt_15f780(src++) != 0;
    e->b002_2 = VariantGetInt_15f780(src++) != 0;
    e->f004 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
