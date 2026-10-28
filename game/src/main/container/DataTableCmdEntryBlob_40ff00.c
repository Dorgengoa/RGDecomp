/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryBlob_40ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xC];
    s16 f00C;
    u8  pad00E[0x16];
    void *f024;
    u8  pad028[0x14];
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
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdEntryBlob_40ff00(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m0;
    void *r0;
    u8   buf0[0x2000] __attribute__((aligned(16)));

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    m0 = Base64Decode_36a700(buf0, SlotGetInt_15f720(src));
    e->f00C = m0;
    e->f024 = 0;
    if (m0 > 0) {
        r0 = ArenaAlloc_3702f0(p->m6C, m0, 0x1);
        e->f024 = r0;
        memcpy(r0, buf0, m0);
    }
    return 1;
}
