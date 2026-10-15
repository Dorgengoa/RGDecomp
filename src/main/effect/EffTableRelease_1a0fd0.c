#include "types.h"

extern void EffTableDestroyAll_1a0240(void *);
extern void OperatorDeleteArray_100820(void *);
extern void EffTableClearRefs_1a1040(void *);
extern void MemStackRefCountDec_14d7c0(void *);

void EffTableRelease_1a0fd0(u8 *o)
{
    EffTableDestroyAll_1a0240(o);
    if (*(void **)(o + 0x118) != 0) {
        OperatorDeleteArray_100820(*(void **)(o + 0x118));
    }
    *(s32 *)(o + 0x114) = 0;
    *(s32 *)(o + 0x110) = 0;
    *(s32 *)(o + 0x118) = 0;
    EffTableClearRefs_1a1040(o);
    if (*(void **)(o + 0x8) != 0) {
        MemStackRefCountDec_14d7c0(*(void **)(o + 0x8));
    }
    *(s32 *)(o + 0x8) = 0;
}
