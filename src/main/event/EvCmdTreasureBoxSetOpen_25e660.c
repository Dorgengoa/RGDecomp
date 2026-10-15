#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 GameFlowGetTreasureBoxId_285ec0(void);
extern s32 GetTreasureBoxPool_3389b0(void);
extern s32 TreasureBoxPoolFindById_339150(s32, s32);
extern void TreasureBoxStartClose_33a550(s32);
extern void TreasureBoxStartOpen_33a5c0(s32);

s32 EvCmdTreasureBoxSetOpen_25e660(s32 arg0)
{
    s32 a;
    s32 b;
    s32 c;

    a = GetTreasureBoxPool_3389b0();
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
