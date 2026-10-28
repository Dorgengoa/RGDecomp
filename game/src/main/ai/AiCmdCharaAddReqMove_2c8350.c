/* rgp:protos */
#define RGP_SELF_AiCmdCharaAddReqMove_2c8350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004DB928;

s32 AiCmdCharaAddReqMove_2c8350(E8 *p0, s32 p1)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    s32 h;
    s32 r;
    s32 x;

    h = D_004DB928;
    if (p1 == 4) {
        h = ScriptSlotGetInt_2cc9c0(p0++);
    }
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[0] = ScriptSlotGetFloat_2cc9a0(p0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] = ScriptSlotGetFloat_2cc9a0(p0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] = ScriptSlotGetFloat_2cc9a0(p0++);
    r = ((s32)GetActionMgr_1fdb50());
    x = ((s32)ActionMgrFindById_233b50(r, h));
    if (x != 0) {
        CharaAddReqMove_238730(x, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
    }
    return 1;
}
