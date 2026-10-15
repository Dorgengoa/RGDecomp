#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  pad006[0x52];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void SlotGetInt_15f720(R8 *q);
extern void TreasureBoxBaseParamRowClearRuntimeMaybe_427f00(Ent *q);

s32 DataTableCmdEntryDefine_427d60(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    if (D_004830FC >= n) return 1;
    t0 = VariantGetInt_15f780(src++);
    e = &p->slots[D_004830FC];
    e->f000 = t0;
    SlotGetInt_15f720(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src);
    TreasureBoxBaseParamRowClearRuntimeMaybe_427f00(e);
    D_004830FC = D_004830FC + 1;
    return 1;
}
