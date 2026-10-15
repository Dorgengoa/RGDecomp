#include "types.h"

extern void HashTableClear_1a9f20(void *);
extern void OperatorDelete_100840(void *);

void EffTableFreeIndex_1a0470(u8 *o)
{
    void *q;

    if (*(void **)(o + 0x10C) != 0) {
        HashTableClear_1a9f20(*(void **)(o + 0x10C));
        q = *(void **)(o + 0x10C);
        if (q != 0) {
            HashTableClear_1a9f20(q);
            OperatorDelete_100840(q);
        }
    }
    *(s32 *)(o + 0x10C) = 0;
}
