/* rgp:protos */
#define RGP_SELF_EffTableFreeIndex_1a0470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

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
