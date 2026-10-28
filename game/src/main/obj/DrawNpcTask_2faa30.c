/* rgp:protos */
#define RGP_SELF_DrawNpcTask_2faa30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DrawNpcTask_2faa30 -- walks a 0xE0-stride array; the count is re-read
   from +0x8 every iteration, and the id increment happens BEFORE the
   pointer step, so this is a `while`, not a `for`. */

/*rgp*/
/*rgp*/
/*rgp*/

void DrawNpcTask_2faa30(u8 *p)
{
    u8 *q;
    s32 i;

    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x32B, 1.0f);
    q = *(u8 **)(p + 0x4);
    if (q != 0) {
        i = 0;
        while (i < *(s16 *)(p + 0x8)) {
            if ((*(u16 *)q & 1) != 0) {
                NpcObjDrawIcons_2fbb20(q);
            }
            i++;
            q += 0xE0;
        }
    }
}
