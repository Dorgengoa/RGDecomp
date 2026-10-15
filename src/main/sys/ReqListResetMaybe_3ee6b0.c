#include "types.h"

extern void ReqEntryInit_3ee700(void *);

/* Callee-saved registers go by declaration order DESCENDING from the highest:
   retail has the pointer in $17 and the counter in $16, so the pointer is
   declared first. */

void ReqListResetMaybe_3ee6b0(u8 *p)
{
    u8 *q;
    s32 i;

    q = p + 8;
    *(s32 *)(p + 0) = 0;
    *(s32 *)(p + 4) = 0;
    for (i = 0; i < 6; i++) {
        ReqEntryInit_3ee700(q);
        q += 0xC;
    }
}
