#include "types.h"

typedef struct Ent {
    s16 h0;         /* 0x00 */
    u16 h2;         /* 0x02 */
    s8 b4a : 6;     /* 0x04 */
    s8 b4b : 1;
    s8 b4c : 1;
    s8 b5;          /* 0x05 */
    s8 b6a : 5;     /* 0x06 */
    s16 b6b : 9;
    s8 b8a : 4;     /* 0x08 */
    s16 b8b : 8;
    s32 mC;         /* 0x0C */
    u32 flags;      /* 0x10 */
    f32 f14[4];     /* 0x14 */
    f32 f24;        /* 0x24 */
    f32 f28;        /* 0x28 */
    f32 f2C;        /* 0x2C */
    f32 f30;        /* 0x30 */
    f32 f34;        /* 0x34 */
} Ent;

typedef struct Mgr {
    u8 pad0[0x7C];
    s16 n;          /* 0x7C */
    u8 pad7E[0xE];
    Ent *tbl;       /* 0x8C */
} Mgr;

extern Mgr *D_004830F8;
extern s16 D_004830FC;
extern s32 VariantGetInt_15f780(s64 *);
extern f32 VariantGetFloat_15f740(s64 *);
extern s32 SlotGetInt_15f720(s64 *);
extern s32 DataTableStoreString_368ab0(Mgr *, s32);
extern s32 DataTableHashName_368a10(Mgr *, s32);
extern void DataTableBitsetClaim_3688b0(Mgr *, u16);

s32 DataTableCmdEntryDefine_3f87f0(s64 *p)
{
    Mgr *m;
    Ent *e;
    s32 a;
    s32 b;
    s32 c;

    m = D_004830F8;
    if (m->n <= 0) {
        return 1;
    }
    if (!(D_004830FC < m->n)) {
        return 1;
    }
    e = &m->tbl[D_004830FC];
    e->h0 = VariantGetInt_15f780(p++);
    e->mC = DataTableStoreString_368ab0(m, SlotGetInt_15f720(p++));
    DataTableBitsetClaim_3688b0(m, e->h2 = DataTableHashName_368a10(m, e->mC));
    e->b6a = VariantGetInt_15f780(p++);
    e->flags = 0;
    a = VariantGetInt_15f780(p++) != 0;
    b = VariantGetInt_15f780(p++) != 0;
    c = VariantGetInt_15f780(p++) != 0;
    if (a) {
        e->flags |= 0x10000000;
    }
    if (b) {
        e->flags |= 0x40000000;
    }
    if (c) {
        e->flags |= 0x20000000;
    }
    a = VariantGetInt_15f780(p++) != 0;
    if (a) {
        e->flags |= 0x08000000;
    }
    e->f14[0] = VariantGetFloat_15f740(p++);
    e->f14[1] = VariantGetFloat_15f740(p++);
    e->f14[2] = VariantGetFloat_15f740(p++);
    e->f14[3] = VariantGetFloat_15f740(p++);
    switch (VariantGetInt_15f780(p++)) {
    case 0:
        break;
    case 1:
        e->flags |= 0x10;
        break;
    case 2:
        e->flags |= 0x20;
        break;
    }
    e->f24 = VariantGetFloat_15f740(p++);
    e->f28 = VariantGetFloat_15f740(p++);
    e->b4a = VariantGetInt_15f780(p++);
    e->f2C = VariantGetFloat_15f740(p++);
    e->f30 = VariantGetFloat_15f740(p++);
    e->f34 = VariantGetFloat_15f740(p++);
    e->b5 = VariantGetInt_15f780(p++);
    e->b4b = VariantGetInt_15f780(p++);
    e->b6b = VariantGetInt_15f780(p++);
    e->b4c = VariantGetInt_15f780(p++);
    e->b8a = VariantGetInt_15f780(p++);
    e->b8b = VariantGetInt_15f780(p++);
    D_004830FC++;
    return 1;
}
