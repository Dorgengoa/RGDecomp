/* rgp:protos */
#define RGP_SELF_ParamScriptMotionCmd_1afac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern u8 D_0049D4E4[0x400];
extern u8 D_0049D4E8[0x400];

s32 ParamScriptMotionCmd_1afac0(s64 *self, s32 n)
{
    (*(s32 *)D_0049D4E4) = VariantGetInt_15f780((s32)self++);
    SlotGetInt_15f720((s32)self++);
    if (n >= 3) {
        (*(s32 *)D_0049D4E8) = VariantGetInt_15f780((s32)self);
    }
    return 1;
}
