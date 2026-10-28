/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget80CarryCloseMaybe_4f9770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9770 -- hide widget 0x80 and clear its latch at +0x3D8.
 * `$4` is never reloaded: `p` is still live in the argument register. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3D8 - 0x37A];
    s16 f3D8;
} Obj;

/*rgp*/

void normal_FieldHudWidget80CarryCloseMaybe_4f9770(Obj *p)
{
    if (p->f378 != 0) {
        UiSetWidgetsVisibleById_291110(p, 0x80, 0, 1);
        p->f3D8 = 0;
    }
}
