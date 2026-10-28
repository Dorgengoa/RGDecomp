/* rgp:protos */
#define RGP_SELF_NpcObjActivateById_2fb6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void NpcObjActivateById_2fb6c0(u8 *p, s32 n)
{
    u8 *r;

    r = ((u8 *)NpcObjFindById_2fb420(p, n));
    if (r != 0) {
        *(s16 *)(r + 0xCC) = 1;
        *(f32 *)(r + 0xC0) = *(f32 *)(r + 0xB4);
        *(s16 *)(p + 0x224) = n;
    }
}
