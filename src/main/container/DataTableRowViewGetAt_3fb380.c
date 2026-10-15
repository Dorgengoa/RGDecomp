#include "types.h"

typedef struct {
    u8 pad0[0x24];
    s16 unk24;
    s32 *unk28;
} S003FB380;

s32 DataTableRowViewGetAt_3fb380(S003FB380 *arg0, s32 arg1)
{
    if ((arg1 >= 0) && (arg1 < arg0->unk24)) {
        return arg0->unk28[arg1];
    }
    return 0;
}
