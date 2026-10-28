/* rgp:protos */
#define RGP_SELF_ActTimeEvnt_23be40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct TagVal {
    f32 f0;
    s32 v4;
    u8 pad8[8];
} TagVal;

extern TagVal *D_00481EA8;
extern s32 D_00481EAC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActTimeEvnt_23be40(u8 *arg0, s32 arg1) {
    TagVal *temp_18;

    if (arg1 < 2) {
        return 0;
    }
    if (D_00481EA8 != NULL && D_00481EAC < 0x40) {
        goto body;
    }
    return 1;
body:
    temp_18 = D_00481EA8 + D_00481EAC;
    temp_18->f0 = ScriptArgGetFloat_23fbc0(arg0);
    if (ScriptCallBuildCharaCmd_23f980(((s32)IdentityPtr_302ac0(&temp_18->v4)), arg0 + 8, arg1 - 1) != 0) {
        D_00481EAC += 1;
    }
    return 1;
}
