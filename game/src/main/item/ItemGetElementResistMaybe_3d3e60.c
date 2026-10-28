/* rgp:protos */
#define RGP_SELF_ItemGetElementResistMaybe_3d3e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3D3E60 { u8 pad000[0x10]; void *f10; };

/*rgp*/

s32 ItemGetElementResistMaybe_3d3e60(struct T3D3E60 *p, s32 i)
{
    u8 *q;

    if (i < 0 || i >= 5) return 0;
    q = ((u8 *)ItemDefGetKind2Or3Data_40e140(p->f10));
    if (q != 0) {
        return *(s8 *)(i + (s32)q + 4);
    }
    return 0;
}
