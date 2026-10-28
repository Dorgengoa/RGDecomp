/* rgp:protos */
#define RGP_SELF_CharaCmdInvincibleTime_22caa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The argc-fail branch jumps INTO the epilogue past `ld $31` (duplicated into
   its delay slot): every exit returns 1, so mwcc tail-merged the constant. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdInvincibleTime_22caa0(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    s32 o;

    if (argc != 1) {
        return 1;
    }
    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0->m00));
    if (o == 0) {
        return 1;
    }
    CharaSetInvincibleTime_2138a0(o, ScriptArgGetFloat_302cf0(p1));
    return 1;
}
