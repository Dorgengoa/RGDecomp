#include "types.h"
typedef struct S00376170 {
    s8 b0;
    s8 b1;
} S00376170;

s32 SaveSlotEntryIsEmpty_376170(S00376170 *s)
{
    if (s->b0 == 0) {
        if (s->b1 == 0) {
            return 1;
        }
    }
    return 0;
}
