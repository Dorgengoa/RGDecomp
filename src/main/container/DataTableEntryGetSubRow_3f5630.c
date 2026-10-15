#include "types.h"

typedef struct E { s32 a; s32 b; s32 c; } E;
typedef struct P { u8 pad0[0x8]; s32 f8; E *fC; } P;

E *DataTableEntryGetSubRow_3f5630(P *p, s32 i)
{
    if (i >= 0 && i < p->f8) return &p->fC[i];
    return 0;
}
