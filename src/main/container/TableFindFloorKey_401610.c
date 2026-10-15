#include "types.h"
typedef struct { s16 v : 10; } B401610;
extern B401610 *IterNext_370040(void *arg0);
extern void IterInit_370170(void *arg0, s32 arg1);

B401610 *TableFindFloorKey_401610(s32 arg0, s32 arg1)
{
    s64 it;
    B401610 *best;
    B401610 *p;
    s32 x;

    best = NULL;
    x = arg0;
    if (x != 0) x += 4;
    IterInit_370170(&it, x);
    while ((p = IterNext_370040(&it)) != NULL) {
        if (p->v > arg1) continue;
        if (best == NULL || best->v < p->v) {
            best = p;
        }
    }
    return best;
}
