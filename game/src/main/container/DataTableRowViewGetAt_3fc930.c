/* rgp:protos */
#define RGP_SELF_DataTableRowViewGetAt_3fc930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s32 a; s32 b; } E;
typedef struct P { u8 pad0[0x10]; s16 f10; u8 pad12[2]; E *f14; } P;

E *DataTableRowViewGetAt_3fc930(P *p, s32 i)
{
    if (i >= 0 && i < p->f10) return &p->f14[i];
    return 0;
}
