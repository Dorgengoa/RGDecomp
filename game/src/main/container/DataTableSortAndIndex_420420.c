/* rgp:protos */
#define RGP_SELF_DataTableSortAndIndex_420420 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct E {
    s16 a;
    s16 b;
} E;

typedef struct R {
    u8 pad0[2];
    s16 unk8;
    u8 padA[0x14];
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
    E e[10];
} O;

/*rgp*/
/*rgp*/

s32 DataTableSortAndIndex_420420(O *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
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
    for (i = 0; i < 10; i++) {
        q = (u8 *)arg0 + i * 4;
        ((E *)(q + 0x98))->a = m;
        ((E *)(q + 0x98))->b = m;
    }
    r = arg0->unk8C;
    for (i = 0; i < arg0->unk7C; i++) {
        k = MainCharaIdToNumber_4016b0(r->unk8)-1;
        if (k < 0 || k >= 9) {
            k = 9;
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
