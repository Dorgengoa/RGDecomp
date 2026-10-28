/* rgp:protos */
#define RGP_SELF_AiCmdRequestActionByNameOrLoco_2cb920 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern s32 D_004DB92C[];

s32 AiCmdRequestActionByNameOrLoco_2cb920(s64 *arg0, s32 arg1) {
    char name[0x80] __attribute__((aligned(16)));
    char buf[0x80] __attribute__((aligned(16)));
    char *s;
    s32 kind;
    s32 h;
    f32 f;

    if (*(s32 *)arg0 == 2) {
        s = ((char *)ScriptSlotGetCodeAddr_2cc980(arg0++));
        strcpy(name, s);
        if (name[0] == '#' && name[1] == '1') {
            name[1] = ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])) + 0x2F;
            if (((unsigned char)CharaIsCurAction_211000(D_004DB92C[0], name)) != 0) {
                strcpy(name, s);
            }
        }
        if (((unsigned char)CharaIsCurAction_211000(D_004DB92C[0], name)) != 0) {
            return 1;
        }
        f = 1.0f;
        if (arg1 >= 2) {
            if (*(s32 *)arg0 != 1) {
                return 0;
            }
            f = ScriptSlotGetFloat_2cc9a0(arg0);
        }
        CharaRequestAction_212410(D_004DB92C[0], name, f);
    } else if (*(s32 *)arg0 == 0) {
        kind = ScriptSlotGetInt_2cc9c0(arg0++);
        if (*(s32 *)arg0 == 2) {
            h = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), kind));
            if (h != 0) {
                s = ((char *)ScriptSlotGetCodeAddr_2cc980(arg0++));
                f = 1.0f;
                if (arg1 >= 3) {
                    f = ScriptSlotGetFloat_2cc9a0(arg0);
                }
                CharaRequestAction_212410(h, s, f);
            }
        } else {
            h = CharaGetActionTable_214cd0(D_004DB92C[0]);
            if (h == 0) {
                return 0;
            }
            switch (kind) {
            case 0:
                ActCfgTableGetStandMotionName_21f590(h, buf, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
                break;
            case 1:
                ActCfgTableGetWalkMotionName_21f550(h, buf, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
                break;
            case 2:
                ActCfgTableGetRunMotionName_21f570(h, buf, ((short)CharaGetBaseActionMode_213830(D_004DB92C[0])));
                break;
            }
            if (((unsigned char)CharaIsCurAction_211000(D_004DB92C[0], buf)) != 0) {
                return 1;
            }
            f = 1.0f;
            if (arg1 > 1) {
                f = ScriptSlotGetFloat_2cc9a0(arg0);
            }
            CharaRequestAction_212410(D_004DB92C[0], buf, f);
        }
    }
    return 1;
}
