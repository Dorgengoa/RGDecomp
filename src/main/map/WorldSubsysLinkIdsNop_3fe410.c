#include "types.h"

typedef struct Iter_FUN_003fe410 {
    u8 d[0x8];
} Iter_FUN_003fe410;

extern void IterInit_370170(Iter_FUN_003fe410 *it, u8 *p);
extern s32 IterNext_370040(Iter_FUN_003fe410 *it);

s32 WorldSubsysLinkIdsNop_3fe410(u8 *a, s32 b)
{
    Iter_FUN_003fe410 it;
    u8 *p;

    if (b == 0) {
        return 0;
    }
    p = a;
    if (a != 0) {
        p = p + 0x88;
    }
    IterInit_370170(&it, p);
    while (IterNext_370040(&it) != 0) {
    }
    return 1;
}
