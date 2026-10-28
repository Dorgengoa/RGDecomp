/* rgp:protos */
#define RGP_SELF_FieldHudFadeOut_204080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void func_4F11D0(const u8 *, f32, f32);
extern u8 D_004BC250[];
extern u8 D_00527020[];

void FieldHudFadeOut_204080(void)
{
    func_4F6ED0(D_00527020);
    func_506D50(D_004BC250, 0.0f, 10.0f);
    func_4F11D0(D_00527020, 0.0f, 10.0f);
}
