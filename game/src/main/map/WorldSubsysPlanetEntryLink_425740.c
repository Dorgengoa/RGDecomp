/* rgp:protos */
#define RGP_SELF_WorldSubsysPlanetEntryLink_425740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

s32 WorldSubsysPlanetEntryLink_425740(struct Obj1 *p0, struct Obj0 *p1)
{
    s16 t0;
    s32 t1;
    s32 q;

    if (p1 == 0) {
        return 0;
    }
    t0 = p1->m08;
    if (t0 < 0) {
        goto fail;
    }
    if (t0 < 2) {
        goto ok;
    }
fail:
    return 0;
ok:
    t1 = p0->m08;
    q = 0;
    if (t1 != 0) {
        q = (t1 + (t0 * 152));
    }
    if (q != 0) {
        WorldSubsysLinkIds_425eb0(q, p0->m04);
    }
    return 1;
}
