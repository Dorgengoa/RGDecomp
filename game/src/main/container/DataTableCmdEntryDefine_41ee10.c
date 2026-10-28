/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_41ee10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  pad006[0x2];
    s16 f008;
    u8  pad00A[0x2];
    s16 f00C;
    s16 f00E;
    void *f010;
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

s32 DataTableCmdEntryDefine_41ee10(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m0;
    void *r0;
    u8   buf0[0x2000] __attribute__((aligned(16)));

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f008 = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src++);
    m0 = Base64Decode_36a700(buf0, SlotGetInt_15f720(src));
    e->f00E = m0;
    e->f010 = 0;
    if (m0 > 0) {
        r0 = ArenaAlloc_3702f0(p->m6C, m0, 0x1);
        e->f010 = r0;
        memcpy(r0, buf0, m0);
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
