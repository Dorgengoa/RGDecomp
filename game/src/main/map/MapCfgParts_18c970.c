/* rgp:protos */
#define RGP_SELF_MapCfgParts_18c970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481250;
extern s32 D_00481254;
extern s32 D_0048125C;
extern s32 D_00481260;
extern s32 D_004812C8;
extern s32 D_004812E4;

s32 MapCfgParts_18c970(s64 *arg0, s32 arg1) {
    s32 t;
    s32 r;
    s32 v;

    t = SlotGetInt_15f720((s32)arg0++);
    D_00481260 = 0;
    if (arg1 >= 2) {
        D_00481260 = VariantGetInt_15f780((s32)arg0);
    }
    v = ((s32)MemStackNew_14e230(0x150, D_0048125C));
    if (v != 0) {
        v = ((s32)NodeObjCtor_18ca70(v));
    }
    if (v == 0) {
        return 0;
    }
    ModelObjSetName_195150(v, t);
    NodeObjSetNameStr_195140(v, ((s32)MemStackStrDup_14cff0(t, D_0048125C)));
    r = ((s32)ObjListAppendNew_1895d0(D_00481250, D_00481260, D_0048125C));
    D_00481254 = r;
    if (r != 0) {
        ListNodeSetData_18ca60(r, v);
        v = 1;
    } else {
        return 0;
    }
    D_004812C8 = 0;
    D_004812E4 = v;
    return v;
}
