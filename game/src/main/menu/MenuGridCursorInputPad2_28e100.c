/* rgp:protos */
#define RGP_SELF_MenuGridCursorInputPad2_28e100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MenuGridCursorInputPad2_28e100(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 a;
    s32 b;
    s32 r0;

    a = p3;
    b = p2;
    r0 = ((unsigned char)IsPad2Enabled_2882c0());
    if (r0 == 0) {
        b = 0;
    }
    return MenuGridCursorInput_28e170(p0, p1, a, b);
}
