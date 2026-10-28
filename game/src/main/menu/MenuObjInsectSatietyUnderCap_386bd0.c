/* rgp:protos */
#define RGP_SELF_MenuObjInsectSatietyUnderCap_386bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of MapAreaModelFindModelCfgEntry_1896e0 (byte-identical, in cunits). */

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x96C];
    s32 m96C;
};

s32 MenuObjInsectSatietyUnderCap_386bd0(struct Obj0 *p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 t0;
    s32 r0;

    t0 = p0->m96C;
    if (t0 != 0) {
        r0 = InsectItemSatietyUnderCap_3d1510(t0, p1, p2, (int)rgp_a3);
        return r0;
    }
    return 0;
}
