#include "types.h"

extern s32 CharaIsCurAction_211000(s32 arg0, void *arg1);
extern void CharaRequestAction_212410(s32 arg0, void *arg1, f32 arg2);
extern s32 CharaGetBaseActionMode_213830(s32 arg0);
extern s32 CharaGetActionTable_214cd0(s32 arg0);
extern void ActCfgTableGetWalkMotionName_21f550(s32 arg0, void *arg1, s32 arg2);
extern void ActCfgTableGetRunMotionName_21f570(s32 arg0, void *arg1, s32 arg2);
extern void ActCfgTableGetStandMotionName_21f590(s32 arg0, void *arg1, s32 arg2);
typedef struct Arg { s32 a; s32 b; } Arg;
extern f32 ScriptSlotGetFloat_2cc9a0(Arg *arg0);
extern s32 ScriptSlotGetInt_2cc9c0(Arg *arg0);
extern s32 D_004DB92C[4];

s32 AiCmdRequestLocoAction_2cb7f0(Arg *arg0, s32 arg1)
{
    u8 sp40[0x80];
    f32 f;
    s32 h;

    h = CharaGetActionTable_214cd0(D_004DB92C[0]);
    if (h == 0) {
        return 0;
    }
    switch (ScriptSlotGetInt_2cc9c0(arg0++)) {
    case 0:
        ActCfgTableGetStandMotionName_21f590(h, sp40, CharaGetBaseActionMode_213830(D_004DB92C[0]));
        break;
    case 1:
        ActCfgTableGetWalkMotionName_21f550(h, sp40, CharaGetBaseActionMode_213830(D_004DB92C[0]));
        break;
    case 2:
        ActCfgTableGetRunMotionName_21f570(h, sp40, CharaGetBaseActionMode_213830(D_004DB92C[0]));
        break;
    }
    if (CharaIsCurAction_211000(D_004DB92C[0], sp40) != 0) {
        return 1;
    }
    f = 1.0f;
    if (arg1 > 1) {
        f = ScriptSlotGetFloat_2cc9a0(arg0);
    }
    CharaRequestAction_212410(D_004DB92C[0], sp40, f);
    return 1;
}
