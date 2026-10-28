/* rgp:protos */
#define RGP_SELF_CharaSysStatusClearAll_3a1460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
struct Obj0 { u8 pad000[0xB94]; s32 mB94; };
struct Obj1 { u8 m00; };

u8 CharaSysStatusClearAll_3a1460(struct Obj0 *p0)
{
    s32 t0;
    s32 l2;
    struct Obj1 *l1;
    s32 l0;
    t0 = p0->mB94;
    l2 = 0;
    l1 = (struct Obj1 *)(t0 + 4);
    l0 = 0;
    do {
        if (l1->m00 != 0) {
            StatusEntryClear_3a5f10(l1, 1);
            l2 = l2 + 1;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 8);
    } while (l0 < 0x20);
    return (l2 != 0);
}
