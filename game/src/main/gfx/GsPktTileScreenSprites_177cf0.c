/* rgp:protos */
#define RGP_SELF_GsPktTileScreenSprites_177cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

typedef struct Rect { s32 x, y, w, h; } __attribute__((aligned(16))) Rect;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GsPktTileScreenSprites_177cf0(s32 o)
{
    Rect sz __attribute__((aligned(16)));
    Rect r __attribute__((aligned(16)));
    Rect p __attribute__((aligned(16)));
    s32 t;
    s32 i;
    s32 j;

    t = GetDrawCtx_15de80();
    GsPktOpenGifTag_13f3b0(o, 6, 0x43, 0, 2);
    ZERO16(&sz);
    sz.x = DrawEnvGetLeft_1450f0(t) * 16;
    sz.y = DrawEnvGetTop_1450c0(t) * 16;
    ZERO16(&r);
    ZERO16(&p);
    for (i = 0; i < DrawEnvGetWidth_1451e0(t); i += 0x40) {
        for (j = 0; j < DrawEnvGetHeight_1451d0(t); j += 0x20) {
            p.y = j * 16;
            p.x = i * 16;
            *(u128 *)&r = *(u128 *)&sz;
            GsPktPushQword_13f170(o, &p);
            r.x = p.x + sz.x;
            r.y = p.y + sz.y;
            GsPktPushQword_13f170(o, &r);
            p.y = (j + 0x20) * 16;
            p.x = (i + 0x40) * 16;
            GsPktPushQword_13f170(o, &p);
            r.x = p.x + sz.x;
            r.y = p.y + sz.y;
            GsPktPushQword_13f170(o, &r);
        }
    }
    GsPktFinalizeTags_13f260(o);
}
