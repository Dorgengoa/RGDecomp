#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x32];
    s16 f032;
    s16 f034;
    s16 f036;
    s16 f038;
    u8  pad03A[0x1E];
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
extern f32  VariantGetFloat_15f740(R8 *q);
extern const f32 D_0045B078;

s32 DataTableCmdEntrySetParams_3fe850(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    f32  t5;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    VariantGetInt_15f780(src++);
    e->f032 = VariantGetInt_15f780(src++);
    e->f034 = VariantGetInt_15f780(src++);
    e->f036 = VariantGetInt_15f780(src++);
    VariantGetFloat_15f740(src++);
    t5 = VariantGetFloat_15f740(src);
    e->f038 = (s32)(t5 * D_0045B078);
    return 1;
}
