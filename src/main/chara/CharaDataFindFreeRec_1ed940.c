#include "types.h"

typedef struct Entry001ed940 {
    u8 pad0[0x62];
    s16 unk62;
    u8 pad64[0x74 - 0x64];
} Entry001ed940;

Entry001ed940 *CharaDataFindFreeRec_1ed940(Entry001ed940 *arg0)
{
    s32 i;
    u8 ok;

    for (i = 0; i < 0x20; i++) {
        ok = arg0[i].unk62 >= 0;
        if (!ok) {
            return &arg0[i];
        }
    }
    return NULL;
}
