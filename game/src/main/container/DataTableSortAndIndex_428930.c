/* rgp:protos */
#define RGP_SELF_DataTableSortAndIndex_428930 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct { s16 first; s16 last; } R428930;
typedef struct { u8 pad0[8]; s16 n8; u8 padA[6]; u8 *p10; u8 pad14[0xC]; } E428930;
typedef struct {
    u8 pad0[0x7A];
    u8 f0 : 1;
    u8 f1 : 7;
    u8 pad7B;
    s16 count;
    u8 pad7E[0x8C - 0x7E];
    E428930 *list;
    u8 pad90[4];
    R428930 r[21];
} S428930;

/*rgp*/

s32 DataTableSortAndIndex_428930(S428930 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 ok;
    s32 i;
    s32 k;
    E428930 *e;

    ok = DataTableBubbleSort_368220((void *)arg0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    arg0->f0 = 0;
    if (ok == 0) {
        return 0;
    }
    for (i = 0; i < 21; i++) {
        arg0->r[i].first = -1;
        arg0->r[i].last = -1;
    }
    e = arg0->list;
    for (i = 0; i < arg0->count; i++, e++) {
        if (e->n8 > 0 && e->p10 != NULL) {
            k = *e->p10;
            if (k >= 20) k = 20;
            if (arg0->r[k].first < 0) {
                arg0->r[k].first = i;
            }
            arg0->r[k].last = i;
        }
    }
    return 1;
}
