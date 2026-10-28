/* rgp:protos */
#define RGP_SELF_EvMapObjHideNamedChildNodesMaybe_3666a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0 { u8 pad000[0xD0]; s32 mD0; u8 pad0D4[0x21C]; s32 m2F0; u8 pad2F4[0x6]; s16 m2FA; };
struct Obj1 { u8 pad000[0x32]; s16 m32; };

s32 EvMapObjHideNamedChildNodesMaybe_3666a0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 l1;
    s32 l0;
    s32 r2;
    struct Obj1 *r3;

    t0 = p0->mD0;
    if ((t0 & 0x2000000) == 0) {
        return 0;
    }
    if (p1 == 0) {
        return 0;
    }
    t1 = p0->m2F0;
    l0 = 0;
    l1 = t1;
    while (l0 < p0->m2FA) {
        r2 = EvMapNameRefGet_367520(l1);
        r3 = NodeObjFindChildByName_195040(p1, r2);
        if (r3 != 0) {
            r3->m32 = 0;
        }
        l0 = (l0 + 1);
        l1 = (l1 + 4);
    }
    return 1;
}
