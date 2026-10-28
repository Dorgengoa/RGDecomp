/* rgp:protos */
#define RGP_SELF_NavCfgCmdGraphCreate_30aa20 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41 agent36): retail `addu a0,v0,$0` before each AlignUp32_1cacc0 is
   a NULL-based address add, `(s32)((u8 *)0 + x)`. */
#include "types.h"

typedef struct Var5f780 { s32 tag; union { s32 i; f32 f; } v; } Var5f780;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048296C;
extern s32 D_00482970;
extern s32 D_00482974;
extern s32 D_00482978;

s32 NavCfgCmdGraphCreate_30aa20(Var5f780 *arg0, s32 arg1)
{
    s32 temp_17;
    s32 temp_16;
    s32 var_18;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    temp_17 = AlignUp32_1cacc0((s32)((u8 *)0 + VariantGetInt_30ab50(arg0)));
    temp_16 = AlignUp32_1cacc0((s32)((u8 *)0 + VariantGetInt_30ab50((Var5f780 *)((u8 *)arg0 + 8))));
    var_18 = 0x80;
    if (arg1 >= 3) {
        var_18 = VariantGetInt_30ab50((Var5f780 *)((u8 *)arg0 + 0x10));
    }
    D_0048296C = NavMgrAddGraph_30ce30((s32)GetNavMgr_2d1950(), D_00482970, D_00482974,
                              D_00482978, temp_17, temp_16, var_18);
    return 1;
}
