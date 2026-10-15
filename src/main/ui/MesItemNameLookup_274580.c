#include "types.h"

extern s16 *FontGetMesItemNameTable_270610(void);

void *MesItemNameLookup_274580(s32 unused0, s32 arg1) {
    s16 *result;
    u8 *base;
    s32 count;
    u8 *addr;
    s32 i;

    result = FontGetMesItemNameTable_270610();
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
