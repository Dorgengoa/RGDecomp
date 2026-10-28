/* rgp:protos */
#define RGP_SELF_TargetRefGetMapObj_2e7050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 TargetRefGetMapObj_2e7050(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = ((short)TargetRefGetKind_2e7130(p0));
    if (r0 == 7) {
        goto ok;
    }
    r1 = ((short)TargetRefGetKind_2e7130(p0));
    if (r1 == 8) {
        goto ok;
    }
    return 0;
ok:
    return p0->m04;
}
