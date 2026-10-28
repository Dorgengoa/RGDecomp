/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuLoadLabels_4efb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFB70 -- 108 bytes, 27 instructions.  Fill eight consecutive
 * string handles from consecutive message ids starting at 0xFA0. */

typedef struct Tbl {
    u8  pad00[0x8];
    s32 f08[8];                     /* +0x08 */
} Tbl;

/*rgp*/

void insect_InsectCmdMenuLoadLabels_4efb70(Tbl *t, void *p)
{
    s32 i;
    s32 k;

    k = 0xFA0;
    for (i = 0; i < 8; i++) {
        t->f08[i] = ((s32)insect_InsectMsgGet_512b70(p, k));
        k++;
    }
}
