/* rgp:protos */
#define RGP_SELF_EventPathTemplateAddPath_300b90 1
#include "port/game_protos.h"
#line 1
/* PARK 2/3: RIGHT LENGTH (51w), 17 bad. LEVER: replacing the m2c
   goto-block_11 shared-tail with THREE SEPARATE inline `return 1;`
   statements (no goto) fixed the length (was 48w with goto, optimization_level
   0-3 sweep on the goto form was null/worse). Residual: the FIRST guard
   (`D_00482840 == 0`) still picks bnel-skip-forward instead of retail's
   beql-direct-to-shared-tail; worth a follow-up trying `goto` on just the
   first guard while keeping the rest as plain `return`. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047F0D0;
extern s32 D_00482840;
extern s32 D_00482844;
extern s32 D_00482848;
extern s32 D_0048284C;

s32 EventPathTemplateAddPath_300b90(s32 pd0, s32 arg1, s32 arg2) {
    s32 var_16;
    s32 temp_17;

    if ((arg1 != 0) && (arg1 != 1)) {
        return 0;
    }
    if ((D_00482840 == 0) || (D_00482844 >= 0x40)) return 1;
    var_16 = 0;
    if (arg1 > 0) {
        var_16 = ParseFlagNames_1ca700(ScriptArgGetStr_301a00((void *)pd0), &D_0047F0D0, 0);
    }
    temp_17 = D_00482840 + (D_00482844 * 0x10);
    EventPathInit_2e46a0(temp_17, EventStrDup_301aa0(arg2), var_16, D_00482848 + (D_0048284C * 8), 0);
    return 1;
}
