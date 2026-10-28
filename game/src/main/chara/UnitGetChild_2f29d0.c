/* rgp:protos */
#define RGP_SELF_UnitGetChild_2f29d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Tbl29D0 {
    u8  pad000[0x3E6];
    s16 count;
    s32 arr[1];
} Tbl29D0;

s32 UnitGetChild_2f29d0(Tbl29D0 *p, s32 i)
{
    if (i >= 0 && i < p->count && p->arr != 0) {
        return p->arr[i];
    }
    return 0;
}
