/* rgp:protos */
#define RGP_SELF_EvMapObjNodeBindFrame_3672d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x144]; s32 m144; };
struct Obj1 { u8 pad000[0x6C]; s32 m6C; };

/*rgp*/
/*rgp*/
/*rgp*/

void EvMapObjNodeBindFrame_3672d0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 r0;
    s32 t1;
    s32 r1;
    s32 r2;

    p0->m144 = 0;
    if (p1 != 0) {
        if (p1->m6C != 0) {
            goto ok;
        }
    }
    return;
ok:
    r0 = EvMapObjNodeGetName_3673e0(p0);
    t1 = p1->m6C;
    r1 = ModelFindFrameIndexByName_151220(t1, r0);
    r2 = ((s32)ModelGetFrame_1511f0(t1, r1));
    p0->m144 = r2;
}
