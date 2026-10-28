/* rgp:protos */
#define RGP_SELF_CharaCmdPlaceAtHomePos_22d560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* p1 is never touched; the guard is argc == 0. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

struct Buf10 {
    u8 b[0x10];
};

s32 CharaCmdPlaceAtHomePos_22d560(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf10 sp20 __attribute__((aligned(16)));
    s32 r0;
    s32 o;

    if (argc != 0) {
        return 0;
    }
    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0->m00));
    if (o == 0) {
        return 1;
    }
    CharaGetHomePos_214350(o, &sp20);
    CharaSetPos_213a40(o, &sp20);
    return 1;
}
