/* rgp:protos */
#define RGP_SELF_MapCfgMoveFlag_18c680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00481254;

s32 MapCfgMoveFlag_18c680(s64 *arg0)
{
    u8 *p;

    if (D_00481254 == 0) {
        return 0;
    }
    p = (u8 *)ListNodeGetData_18a370(D_00481254);
    if (p == NULL) {
        return 0;
    }
    *(s32 *)(p + 0x124) = 0;
    if (VariantGetInt_15f780(arg0++) != 0) {
        *(s32 *)(p + 0x124) |= 1;
    }
    if (VariantGetInt_15f780(arg0++) != 0) {
        *(s32 *)(p + 0x124) |= 2;
    }
    if (VariantGetInt_15f780(arg0++) != 0) {
        *(s32 *)(p + 0x124) |= 4;
    }
    if (VariantGetInt_15f780(arg0) != 0) {
        *(s32 *)(p + 0x124) |= 8;
    }
    return 1;
}
