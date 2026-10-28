/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialGridSetCell_4f33e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Box {
    s16 f00;
    s16 f02;
    u8  pad04[0x18];
    u16 f1C;
} Box;

typedef struct Box2 {
    s16 f00;
    s16 f02;
    u8  pad04[0x16];
    s16 f1A;
} Box2;

typedef struct Ctx {
    u8    pad00[0x40];
    void *f40;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialGridSetCell_4f33e0(Ctx *a, s32 b, s32 c, s32 d, s32 e)
{
    s32   id;
    Box  *p;
    Box2 *q;

    if (a->f40 == 0) {
        return 0;
    }
    id = b + 1;
    p = ((Box *)UiGetWidgetSprite_28fe10(a->f40, (u16)b, 0));
    if (p == 0) {
        return 0;
    }
    q = ((Box2 *)UiGetWidgetSubItem_28f2b0(a->f40, (u16)id, 0));
    if (q == 0) {
        return 0;
    }
    q = (Box2 *)((u8 *)q + d * 32);
    p = (Box *)((u8 *)p + d * 32);
    UiSetItemIconUv_288e50(p, c, 0x28, 0x2D);
    p->f00 = (d % 8) * 44 + 28;
    p->f02 = (d / 8) * 50 + 27;
    p->f1C = 0;
    q->f00 = p->f00 + 0x25;
    q->f02 = p->f02 + 0x1B;
    q->f1A = 2;
    if (e != 0) {
        p->f1C |= 0xA;
        q->f1A |= 0x20;
    } else {
        p->f1C |= 0x202;
        q->f1A |= 0x40;
    }
    return 1;
}
