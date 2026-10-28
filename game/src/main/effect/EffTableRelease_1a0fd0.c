/* rgp:protos */
#define RGP_SELF_EffTableRelease_1a0fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
