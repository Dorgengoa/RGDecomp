/* rgp:protos */
#define RGP_SELF_DataTableSortAndIndex_4128c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/

typedef struct {
    s16 a;
    s16 b;
    s16 c;
} E;

typedef struct {
    u8 f0 : 1;
    u8 f1 : 7;
} B;

s32 DataTableSortAndIndex_4128c0(void *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    void *temp_4;
    u8 *src;
    s32 k;
    u8 r;
    s32 i;
    s32 temp_2;
    s16 key;
    s16 v;
    E *found;
    E *e;
    s32 j;

    k = 0;
    r = DataTableBubbleSort_368220((void *)arg0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    ((B *)((u8 *)arg0 + 0x7A))->f0 = k;
    if (!r) {
        return 0;
    }
    i = 0;
    do {
        temp_2 = i * 6;
        i += 1;
        temp_4 = (u8 *)arg0 + temp_2;
        *(s16 *)((u8 *)temp_4 + 0x98) = -1;
        *(s16 *)((u8 *)temp_4 + 0x9A) = -1;
        *(s16 *)((u8 *)temp_4 + 0x9C) = -1;
    } while (i < 0x65);
    src = *(u8 **)((u8 *)arg0 + 0x8C);
    for (k = 0; k < *(s16 *)((u8 *)arg0 + 0x7C); k++) {
        key = *(s16 *)(src + 2);
        found = NULL;
        e = (E *)((u8 *)arg0 + 0x98);
        j = 0;
        while (j < 100) {
            v = e->a;
            if (v == key) {
                found = e;
                break;
            }
            if (v < 0) {
                e->a = key;
                found = e;
                break;
            }
            j++;
            e++;
        }
        if (found == NULL) {
            found = (E *)((u8 *)arg0 + 0x2F0);
        }
        if (found->b < 0) {
            found->b = k;
        }
        found->c = k;
        src += 0x1C;
    }
    return 1;
}
