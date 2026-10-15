#include "types.h"
/* insect 0x00511E20 -- 52 bytes.  A DOWNWARD scan of the 8 pointers at +0xC;
 * the loop guard is `bgezl $3` so the counter is signed and the test is
 * `>= 0`. */
typedef struct Slots {
    u8    pad00[0xC];
    void *arr[8];                   /* +0x0C */
} Slots;

void *insect_InsectCursorSetGetCurPage_511e20(Slots *s)
{
    s32 i;

    for (i = 7; i >= 0; i--) {
        if (s->arr[i] != 0) {
            return s->arr[i];
        }
    }
    return 0;
}
