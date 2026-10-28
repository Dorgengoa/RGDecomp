/* rgp:protos */
#define RGP_SELF_EvCmdCharaSetSrtVec40_25eb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E25eb70 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaSetSrtVec40_25eb70(struct E25eb70 *p)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    s32 a;
    s32 obj;

    a = ScriptGetInt_26a2a0(p++);
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), a));
    if (obj == 0) {
        return 0;
    }
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[0] = TaggedGetFloat_26a280(p++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] = TaggedGetFloat_26a280(p++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] = TaggedGetFloat_26a280(p);
    CharaSetSrtVec40FromVec_238780(obj, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
    return 1;
}
