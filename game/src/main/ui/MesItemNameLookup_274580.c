/* rgp:protos */
#define RGP_SELF_MesItemNameLookup_274580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void *MesItemNameLookup_274580(s32 unused0, s32 arg1) {
    s16 *result;
    u8 *base;
    s32 count;
    u8 *addr;
    s32 i;

    result = ((s16 *)FontGetMesItemNameTable_270610((int)unused0));
    count = *result;
    base = (u8 *)result + 2;
    for (i = 0; i < count; i++) {
        addr = base + i * 4;
        if (arg1 == *(u16 *)(addr + 2)) {
            return base + count * 2 + *(u16 *)(addr + 4) * 2;
        }
    }
    return NULL;
}
