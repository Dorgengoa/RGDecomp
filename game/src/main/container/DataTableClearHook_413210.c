/* rgp:protos */
#define RGP_SELF_DataTableClearHook_413210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Efunc_00413210 { s16 x; s16 y; };
struct Pfunc_00413210 { u8 pad000[0x94]; s32 f94; struct Efunc_00413210 e[7]; };

void DataTableClearHook_413210(struct Pfunc_00413210 *p)
{
    s32 i;

    p->f94 = 0;
    for (i = 0; i < 7; i++) {
        p->e[i].x = -1;
        p->e[i].y = -1;
    }
}
