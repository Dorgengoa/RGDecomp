#include "types.h"

struct Efunc_00420830 { s16 x; s16 y; };
struct Pfunc_00420830 { u8 pad000[0x94]; s32 f94; struct Efunc_00420830 e[10]; };

void DataTableClearHook_420830(struct Pfunc_00420830 *p)
{
    s32 i;

    p->f94 = 0;
    for (i = 0; i < 10; i++) {
        p->e[i].x = -1;
        p->e[i].y = -1;
    }
}
