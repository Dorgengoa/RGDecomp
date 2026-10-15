#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x36];
    f32 f038;
    f32 f03C;
    f32 f040;
    f32 f044;
    s32 f048;
    s32 f04C;
    u8  pad050[0x8];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern f32  VariantGetFloat_15f740(R8 *q);

s32 DataTableCmdEntryDefine_41d050(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = (s32)(VariantGetFloat_15f740(src++));
    e->f038 = VariantGetFloat_15f740(src++);
    e->f03C = VariantGetFloat_15f740(src++);
    e->f040 = VariantGetFloat_15f740(src++);
    e->f044 = 1.0f;
    e->f044 = VariantGetFloat_15f740(src);
    e->f048 = 0;
    e->f04C = 0;
    D_004830FC = D_004830FC + 1;
    return 1;
}
