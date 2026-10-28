/* rgp:protos */
#define RGP_SELF_FieldHudBtlEscGetResult_203cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00527020[];

/*rgp*/

s16 FieldHudBtlEscGetResult_203cb0(void)
{
    s16 v;

    s16 r;
    v = (s16)((short)func_4F0A20(D_00527020));
    if (v != 2) {
        if (v != 1) {
            return 0;
        }
        r = 1;
    } else {
        r = 2;
    }
    return r;
}
