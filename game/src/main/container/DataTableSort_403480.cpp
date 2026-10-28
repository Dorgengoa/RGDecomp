/* rgp:protos */
#line 1
#include "types.h"

struct T403480 { u8 pad000[0x7A]; u8 f7A_b : 1; u8 f7A_a : 7; };

extern "C" bool DataTableBubbleSort_368220(struct T403480 *, int, int, int);

extern "C" u32 DataTableSort_403480(struct T403480 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    bool r;

    r = DataTableBubbleSort_368220(p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    p->f7A_b = 0;
    return (bool)(r);
}
