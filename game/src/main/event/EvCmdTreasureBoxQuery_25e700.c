/* rgp:protos */
#define RGP_SELF_EvCmdTreasureBoxQuery_25e700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4_25e700;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdTreasureBoxQuery_25e700(s64 *arg0)
{
    V4_25e700 a __attribute__((aligned(16)));
    V4_25e700 b __attribute__((aligned(16)));
    V4_25e700 c __attribute__((aligned(16)));
    s32 o;
    f32 f;

    o = ((s32)GetTreasureBoxPool_3389b0());
    o = TreasureBoxPoolFindById_339150(o, GameFlowGetTreasureBoxId_285ec0());
    if (o == 0) {
        return 0;
    }
    switch (ScriptGetInt_26a2a0(arg0++)) {
    case 0:
        ScriptSetRefInt_26a1e0(arg0, TreasureBoxGetItemId_33ad90(o));
        break;
    case 2:
        if (TreasureBoxIsOpened_33a240(o) != 0) {
            ScriptSetRefInt_26a1e0(arg0, 2);
        } else if (TreasureBoxCanOpenThunkMaybe_33abd0(o) != 0) {
            ScriptSetRefInt_26a1e0(arg0, 1);
        } else {
            ScriptSetRefInt_26a1e0(arg0, 0);
        }
        break;
    case 3:
        if (TreasureBoxIsLockedMaybe_33acf0(o) != 0) {
            { s32 z_ = 0; ScriptSetRefInt_26a1e0(arg0, TreasureBoxGetKind_33adb0(o) + z_); }
        } else {
            ScriptSetRefInt_26a1e0(arg0, 0);
        }
        break;
    case 4:
        ScriptSetRefInt_26a1e0(arg0, TreasureBoxGetTrapKind_33aaf0(o));
        break;
    case 5:
        ScriptSetRefInt_26a1e0(arg0, TreasureBoxIsEncounterBox_33aac0(o));
        break;
    case 6:
        TreasureBoxGetPos_33ae30(o, &a);
        ScriptSetRefFloat_26a1c0(arg0++, a.x);
        ScriptSetRefFloat_26a1c0(arg0++, a.y);
        ScriptSetRefFloat_26a1c0(arg0, a.z);
        break;
    case 7:
        TreasureBoxGetRot_33ae20(o, &b);
        ScriptSetRefFloat_26a1c0(arg0++, b.x);
        ScriptSetRefFloat_26a1c0(arg0++, b.y);
        ScriptSetRefFloat_26a1c0(arg0, b.z);
        break;
    case 8:
        TreasureBoxGetRot_33ae20(o, &c);
        f = c.y;
        ScriptSetRefFloat_26a1c0(arg0++, Sinf_128fd0(f));
        ScriptSetRefFloat_26a1c0(arg0++, 0.0f);
        ScriptSetRefFloat_26a1c0(arg0, Cosf_128d30(f));
        break;
    case 1:
        ScriptSetRefInt_26a1e0(arg0, ((short)TreasureBoxGetItemCount_33ad70(o)));
        break;
    }
    return 1;
}
