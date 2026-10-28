/* rgp:protos */
#define RGP_SELF_ClsnInfoSeNo_23bb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
/*rgp*/
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ClsnInfoSeNo_23bb30(s32 pad0, s32 arg1) {
    s32 temp_16;
    s32 a;
    s32 n;
    s32 r;

    if (arg1 != 1) {
        return 0;
    }
    if (D_00481EB0 == 0 || D_00481EB4 <= 0) {
        return 1;
    }
    a = D_00481EB0;
    n = D_00481EB4;
    temp_16 = (a + (n << 5)) - 0x20;
    r = ScriptArgGetInt_23fc00((void *)pad0);
    ClsnInfoSetSeNo_228160(temp_16 + 4, r);
    return 1;
}
