/* rgp:protos */
#define RGP_SELF_DataTableSortAndIndex_412f70 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct E {
    s16 a;
    s16 b;
} E;

typedef struct R {
    u8 pad0[8];
    s16 unk8;
    u8 padA[0x16];
} R;

typedef struct O {
    u8 pad0[0x7A];
    u8 flag : 1;
    u8 rest : 7;
    u8 pad7B;
    s16 unk7C;
    u8 pad7E[0xE];
    R *unk8C;
    u8 pad90[8];
    E e[7];
} O;

/*rgp*/

s32 DataTableSortAndIndex_412f70(O *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 i;
    s32 k;
    R *r;
    u8 *q;
    s16 m;
    s16 *pa;
    E *ep;
    u8 c;

    c = DataTableBubbleSort_368220((void *)arg0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    arg0->flag = 0;
    if (c == 0) {
        return 0;
    }
    m = -1;
    for (i = 0; i < 7; i++) {
        q = (u8 *)arg0 + i * 4;
        ((E *)(q + 0x98))->a = m;
        ((E *)(q + 0x98))->b = m;
    }
    r = arg0->unk8C;
    for (i = 0; i < arg0->unk7C; i++) {
        k = r->unk8;
        if (k < 0 || k >= 6) {
            k = 6;
        }
        q = (u8 *)arg0 + k * 4;
        pa = (s16 *)(q + 0x98);
        if (*pa < 0) {
            *pa = i;
        }
        *(s16 *)(q + 0x9A) = i;
        r++;
    }
    return 1;
}
