/* rgp:protos */
#define RGP_SELF_EvCmdSetObjPos_267570 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E8D0;
extern f32 D_0047E8D4;
extern f32 D_0047E8D8;
extern f32 D_0047E8DC;

s32 EvCmdSetObjPos_267570(s64 *arg0, s32 arg1)
{
    f32 t[4] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; char m2[0xc]; })];
    s32 id;
    s32 obj;
    s32 r;
    s32 k;
    f32 *p;

    id = ScriptGetInt_26a2a0((s32)arg0++);
    obj = ((s32)EventSceneGetObj_2676e0(id));
    if (obj == 0) {
        return 0;
    }
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[0] = TaggedGetFloat_26a280((s32)arg0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] = TaggedGetFloat_26a280((s32)arg0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] = TaggedGetFloat_26a280((s32)arg0++);
    p = t;
    p[0] = D_0047E8D0;
    p[1] = D_0047E8D4;
    p[2] = D_0047E8D8;
    p[3] = D_0047E8DC;
    t[0] = (*(f32 (*)[3])(rgp_blk1 + 0x0))[0];
    t[1] = (*(f32 (*)[3])(rgp_blk1 + 0x0))[1];
    t[2] = (*(f32 (*)[3])(rgp_blk1 + 0x0))[2];
    ModelSetPos_151110(obj, t);
    r = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), id));
    if (r != 0) {
        k = 0;
        if (arg1 >= 5) {
            k = ScriptGetInt_26a2a0((s32)arg0);
        }
        switch (k) {
        case 0:
            CharaSetPosVec_2387a0(r, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
            break;
        case 1:
            CharaSetPos_213a40(r, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
            break;
        case 9999:
            CharaSetPos_213a40(r, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
            CharaSetHomePos_214330(r, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
            break;
        }
    }
    return 1;
}
