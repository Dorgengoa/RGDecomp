/* rgp:protos */
#define RGP_SELF_ReqListResetMaybe_3ee6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
