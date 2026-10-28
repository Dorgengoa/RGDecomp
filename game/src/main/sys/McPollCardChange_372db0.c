/* rgp:protos */
#define RGP_SELF_McPollCardChange_372db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void sceMcInit_12c648();
extern s32 sceMcEnd_12c870();
extern s32 sceMcSync_12d098(s32, s32, s32);
extern s32 sceMcGetInfo_12d1b8(s32, s32, s32 *, s32, s32);
/*rgp*/
extern s32 D_0048316C;
extern s32 D_00483170;
extern s32 D_00483174;
extern s32 D_00483178[2];
extern s16 D_00483180;
extern u8 D_00483184;

s16 McPollCardChange_372db0(void) {
    s16 temp_2;
    s32 temp_4;
    s16 var_16;

    if ((D_00483184 == 0) && (D_00483180 == 0)) {
        sceMcInit_12c648();
        if (sceMcGetInfo_12d1b8(D_00483170, 1, &D_0048316C, 0, 0) == 0) {
            D_00483184 = 1;
        } else {
            sceMcEnd_12c870();
        }
    }
    if (D_00483184 != 0) {
        D_00483174 = sceMcSync_12d098(1, 0, 0);
    }
    if (D_00483180 > 0) {
        temp_2 = D_00483180 - 1;
        D_00483180 = temp_2;
        if (temp_2 <= 0) {
            D_00483180 = 0;
        }
    }
    if ((D_00483184 != 0) && (D_00483174 != 0)) {
        var_16 = 0;
        temp_4 = D_00483178[D_00483170];
        if ((temp_4 == 0) && (D_0048316C == 2)) {
            var_16 = 2;
        } else if ((temp_4 == 2) && (D_0048316C == 0)) {
            var_16 = 1;
            McSaveClearedFlagReset_372fa0(*(volatile s32 *)&D_00483170);
        }
        D_00483178[D_00483170] = D_0048316C;
        sceMcEnd_12c870(D_0048316C);
        D_00483184 = 0;
        D_00483170 = (D_00483170 + 1) & 1;
        D_00483180 = 0xA;
        return var_16;
    }
    return 0;
}
