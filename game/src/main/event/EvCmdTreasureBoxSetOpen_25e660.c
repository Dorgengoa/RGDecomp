/* rgp:protos */
#define RGP_SELF_EvCmdTreasureBoxSetOpen_25e660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdTreasureBoxSetOpen_25e660(s32 arg0)
{
    s32 a;
    s32 b;
    s32 c;

    a = ((s32)GetTreasureBoxPool_3389b0());
    b = TreasureBoxPoolFindById_339150(a, GameFlowGetTreasureBoxId_285ec0());
    if (b == 0) {
        return 0;
    }
    c = ScriptGetInt_26a2a0(arg0);
    switch (c) {
    case 0:
        TreasureBoxStartClose_33a550(b);
        break;
    case 1:
        TreasureBoxStartOpen_33a5c0(b);
        break;
    }
    return 1;
    return 0;
}
