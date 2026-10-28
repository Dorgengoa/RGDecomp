/* rgp:protos */
#define RGP_SELF_FieldHudFadeIn_203ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void func_4F11D0(const u8 *, f32, f32);
/*rgp*/
extern u8 D_004BC250[];
extern u8 D_00527020[];

void FieldHudFadeIn_203ee0(void)
{
    func_4F6F00(D_00527020);
    func_506D50(D_004BC250, 1.0f, 10.0f);
    func_4F11D0(D_00527020, 1.0f, 10.0f);
    func_4F08A0(D_00527020);
}
