#include "types.h"

struct T403480 { u8 pad000[0x7A]; u8 f7A_b : 1; u8 f7A_a : 7; };

extern "C" bool DataTableBubbleSort_368220(struct T403480 *p);

extern "C" bool DataTableSort_403480(struct T403480 *p)
{
    bool r;

    r = DataTableBubbleSort_368220(p);
    p->f7A_b = 0;
    return r;
}
