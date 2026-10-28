/* rgp:protos */
#define RGP_SELF_MenuChoiceDim_29c130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T29C130 { u8 pad000[0x4C4]; void *f4C4; };

extern u16 D_0047EC18[4];
extern f32 D_0047D288;
/*rgp*/

s32 MenuChoiceDim_29c130(struct T29C130 *p, s32 i)
{
    f32 c = D_0047D288;

    UiSetWidgetColor_2905b0(p->f4C4, D_0047EC18[(s16)i], c, c, c, 1.0f);
    return 1;
}
