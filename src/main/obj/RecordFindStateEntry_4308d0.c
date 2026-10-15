#include "types.h"

extern const s16 D_00468D70;

void *RecordFindStateEntry_4308d0(void *arg0) {
    u8 *p;
    s32 f0;
    s32 f4;
    s32 f8;

    p = *(u8 **)((u8 *)arg0 + 0x1188);
    f0 = *(s32 *)(p + 0);
    f4 = *(s32 *)(p + 4);
    f8 = *(s32 *)(p + 8);
    p = (u8 *)&D_00468D70;
    while (*(s16 *)(p + 0) != -1) {
        if ((*(s16 *)(p + 0) == f0) && (*(s16 *)(p + 2) == f4) && (*(s16 *)(p + 4) == f8)) {
            return p;
        }
        p += 0xA;
    }
    return NULL;
}
