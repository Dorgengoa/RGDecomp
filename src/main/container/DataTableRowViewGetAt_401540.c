#include "types.h"

typedef struct E { s32 a; s32 b; s32 c; s32 d; } E;
typedef struct P { u8 pad0[0x8]; s16 f8; u8 padA[2]; E *fC; } P;

E *DataTableRowViewGetAt_401540(P *p, s32 i)
{
    if (i >= 0 && i < p->f8) return &p->fC[i];
    return 0;
}
