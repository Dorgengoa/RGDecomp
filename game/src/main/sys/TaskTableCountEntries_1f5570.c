/* rgp:protos */
#define RGP_SELF_TaskTableCountEntries_1f5570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem_FUN_001f5570 {
    s32 f00;
    u8 pad004[0xC];
} Elem_FUN_001f5570;

s32 TaskTableCountEntries_1f5570(Elem_FUN_001f5570 *p)
{
    s32 i;

    if (p == 0) {
        return 0;
    }
    i = 0;
    while (p->f00 != 0) {
        p++;
        i++;
    }
    return i;
}
