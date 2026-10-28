/* rgp:protos */
#define RGP_SELF_ActorFindById_3eb8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x4];
    s32 m1C;
};

s32 ActorFindById_3eb8d0(struct Obj0 *p0, s32 p1)
{
    s32 rv;
    s32 t0;
    s32 t1;

    rv = 0;
    t0 = p0->m14;
    if (t0 != 0) {
        rv = ((s32)CharaMgrPoolFindByIdThunk2_3a8c60(t0, (int)p1));
    }
    if (rv == 0) {
        t1 = p0->m1C;
        if (t1 != 0) {
            rv = ((s32)ObjFindByIdThunk2_3bb3a0(t1, p1));
        }
    }
    return rv;
}
