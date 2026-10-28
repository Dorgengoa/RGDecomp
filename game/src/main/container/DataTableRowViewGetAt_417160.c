/* rgp:protos */
#define RGP_SELF_DataTableRowViewGetAt_417160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s32 a; s32 b; s32 c; s32 d; s32 e; } E;
typedef struct P { u8 pad0[0x1C]; s32 f1C; E *f20; } P;

E *DataTableRowViewGetAt_417160(P *p, s32 i)
{
    if (i >= 0 && i < p->f1C) return &p->f20[i];
    return 0;
}
