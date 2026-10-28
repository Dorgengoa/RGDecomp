/* rgp:protos */
#define RGP_SELF_FieldHudHideAll_203e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00527020[];
extern u8 D_004BC250[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FieldHudHideAll_203e20(void)
{
    func_4F6ED0(D_00527020);
    func_506B70(D_004BC250, 0x59DC);
    func_4F1940(D_00527020);
    BtlChgMenuCloseThunk_4f9d70();
}
