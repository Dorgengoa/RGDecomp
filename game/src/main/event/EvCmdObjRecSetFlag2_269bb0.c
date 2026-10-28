/* rgp:protos */
#define RGP_SELF_EvCmdObjRecSetFlag2_269bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;

s32 EvCmdObjRecSetFlag2_269bb0(s64 *arg0, s32 arg1)
{
    s32 flag;
    s32 v;

    flag = 1;
    switch (arg1) {
    case 1:
        v = ScriptGetInt_26a2a0((s32)arg0);
        goto blk;
    case 2:
        flag = ScriptGetInt_26a2a0((s32)arg0++);
        v = ScriptGetInt_26a2a0((s32)arg0);
        goto blk;
    default:
        return 0;
    }
blk:
    if (flag != 0) {
        ObjRecSetFlag2_1c3e80(D_00481F78, 1, v);
    } else {
        ObjRecClearFlag2_1c3e40(D_00481F78, 1, v);
    }
    return 1;
}
