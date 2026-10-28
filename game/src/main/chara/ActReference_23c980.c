/* rgp:protos */
#define RGP_SELF_ActReference_23c980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00481EA0;
extern s32 D_00481EA4;

s32 ActReference_23c980(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 *temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if (D_00481EA0 == 0 || D_00481EA4 >= 0x10) {
        return 1;
    }
    temp_17 = (s32 *)(D_00481EA0 + (D_00481EA4 * 8));
    temp_16 = ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)));
    ActReferenceInit_228660(temp_17, temp_16, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 8))));
    if (temp_17[0] == 0 || temp_17[1] == 0) {
        return 1;
    }
    D_00481EA4 += 1;
    return 1;
}
