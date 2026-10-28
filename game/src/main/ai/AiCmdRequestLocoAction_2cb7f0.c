/* rgp:protos */
#define RGP_SELF_AiCmdRequestLocoAction_2cb7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct Arg { s32 a; s32 b; } Arg;
/*rgp*/
/*rgp*/
extern s32 D_004DB92C[4];

s32 AiCmdRequestLocoAction_2cb7f0(Arg *arg0, s32 arg1)
{
    u8 sp40[0x80] __attribute__((aligned(16)));
    f32 f;
    s32 h;

    h = CharaGetActionTable_214cd0(D_004DB92C[0]);
    if (h == 0) {
        return 0;
    }
    switch (ScriptSlotGetInt_2cc9c0(arg0++)) {
    case 0:
        ActCfgTableGetStandMotionName_21f590(h, sp40, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
        break;
    case 1:
        ActCfgTableGetWalkMotionName_21f550(h, sp40, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
        break;
    case 2:
        ActCfgTableGetRunMotionName_21f570(h, sp40, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
        break;
    }
    if (((unsigned char)CharaIsCurAction_211000(D_004DB92C[0], sp40)) != 0) {
        return 1;
    }
    f = 1.0f;
    if (arg1 > 1) {
        f = ScriptSlotGetFloat_2cc9a0(arg0);
    }
    CharaRequestAction_212410(D_004DB92C[0], sp40, f);
    return 1;
}
