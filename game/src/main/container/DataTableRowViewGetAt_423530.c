/* rgp:protos */
#define RGP_SELF_DataTableRowViewGetAt_423530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { u8 b[0x10]; } E;
typedef struct P { u8 pad0[0x14]; s32 f14; E *f18; } P;

E *DataTableRowViewGetAt_423530(P *p, s32 i)
{
    if (i >= 0 && i < p->f14) return &p->f18[i];
    return 0;
}
