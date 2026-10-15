#include "types.h"

struct T208C00 { u8 pad000[0x30]; void **f30; };

extern s32 TaskTableGetEntry_27c2e0(s32 i);

s32 TaskEntryOfDebugItem_208c00(struct T208C00 *p)
{
    void **base;
    void **q;
    void *v;

    base = p->f30;
    if (base == 0) return 0;
    q = base;
    while ((v = *q) != 0) {
        if (p == v) {
            return TaskTableGetEntry_27c2e0(q - base);
        }
        q++;
    }
    return 0;
}
