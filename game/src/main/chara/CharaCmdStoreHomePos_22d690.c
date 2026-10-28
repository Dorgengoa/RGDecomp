/* rgp:protos */
#define RGP_SELF_CharaCmdStoreHomePos_22d690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdStoreHomePos_22d690(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 r0;
    s32 o;

    if (argc != 0 && argc != 3) {
        return 0;
    }
    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0->m00));
    if (o == 0) {
        return 1;
    }
    CharaGetPlacedPosMaybe_238280(o, v);
    CharaSetHomePos_214330(o, v);
    return 1;
}
