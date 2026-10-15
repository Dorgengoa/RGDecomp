#include "types.h"
typedef struct S00376050 {
    s8 b0;
    s8 b1;
} S00376050;

s32 SaveSlotEntryIsValid_376050(S00376050 *s)
{
    if (s->b0 == 1) {
        if (s->b1 == 0) {
            return 1;
        }
    }
    return 0;
}
