/* rgp:protos */
#define RGP_SELF_ParamScriptSeStartCmd_1af8d0 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0049D45C[0x40];
extern s32 D_0049D4E0[0x40];
extern s32 D_0049D4E4[0x40];
extern s32 D_0049D4E8[0x40];
extern s32 D_0049D4F0[0x40];
extern s32 D_0049D4F4[0x40];
extern s32 D_0049D4F8[0x40];
extern s32 D_0049D4FC[0x40];
extern s32 D_0049D500[0x40];

s32 ParamScriptSeStartCmd_1af8d0(s32 pad0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 n;

    a = D_0049D45C[0];
    b = D_0049D4E0[0];
    D_0049D4F8[0] = 0;
    D_0049D4FC[0] = 0;
    if (a == 0 || b == 0) {
        return 0;
    }
    if (arg1 <= 0) {
        return 0;
    }
    n = VariantGetInt_15f780((void *)pad0);
    if (n <= 0) {
        return 0;
    }
    if (D_0049D4E4[0] < 0) {
        return 0;
    }
    if (D_0049D4E8[0] < 0) {
        return 0;
    }
    if (((s32)MotionListFindSubEntry_172430(b + 0x1F0, D_0049D4E8[0], D_0049D4E4[0])) == 0) {
        return 0;
    }
    D_0049D4F0[0] = D_0049D4E8[0];
    D_0049D4F4[0] = D_0049D4E4[0];
    D_0049D4F8[0] = n;
    D_0049D4FC[0] = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(n * 0x14 + 0x10, a)), ParamScriptSeEntryCtor_1afa20, 0, 0x14, n));
    if (D_0049D4FC[0] == 0) {
        return 0;
    }
    D_0049D500[0] = 0;
    return 1;
}
