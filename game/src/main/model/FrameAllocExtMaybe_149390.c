/* rgp:protos */
#define RGP_SELF_FrameAllocExtMaybe_149390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void FrameAllocExtMaybe_149390(u8 *p0, void *rgp_a1)
{
    s32 *q;

    if (*(s32 **)(p0 + 0x20) == 0) {
        q = ((s32 *)MemStackNew_14e230(0x20, (void *)rgp_a1));
        if (q != 0) {
            *q = 0;
        }
        *(s32 **)(p0 + 0x20) = q;
    }
}
