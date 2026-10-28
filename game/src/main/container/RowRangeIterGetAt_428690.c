/* rgp:protos */
#define RGP_SELF_RowRangeIterGetAt_428690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x7C]; s16 n7C; u8 pad2[0x8C - 0x7E]; u8 *p8C; } Tbl;
typedef struct { s32 pad0; Tbl *t; s16 v8; s16 vA; } Obj;

void *RowRangeIterGetAt_428690(Obj *arg0, s32 arg1)
{
    Tbl *v6;
    s32 v3;
    s32 v2;

    v6 = arg0->t;
    if (v6 == NULL) {
        return 0;
    }
    v3 = arg0->v8;
    if (v3 < 0 || (v2 = arg0->vA) < 0) {
        return 0;
    }
    v3 += arg1;
    if (v2 < v3) {
        return 0;
    }
    return (v3 >= 0 && v3 < v6->n7C) ? v6->p8C + (v3 << 5) : 0;
}
