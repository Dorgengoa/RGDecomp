#include "types.h"

extern void *IterNext_370040(void *);
extern void IterInit_370170(void *, void *);

void *ItemDefFindByKeys_40c6b0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp58[8];
    u8 *p;
    u8 *t;

    p = arg0;
    if (arg0 != 0) {
        p += 0x88;
    }
    IterInit_370170(sp58, p);
    while ((t = IterNext_370040(sp58)) != 0) {
        if (*(s8 *)(t + 2) == arg1 && *(s16 *)(t + 4) == arg2 && *(s8 *)(t + 3) == arg3 && *(s16 *)(t + 6) == arg4) {
            return t;
        }
    }
    return 0;
}
