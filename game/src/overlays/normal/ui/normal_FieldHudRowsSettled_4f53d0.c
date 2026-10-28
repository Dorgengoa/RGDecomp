/* rgp:protos */
#define RGP_SELF_normal_FieldHudRowsSettled_4f53d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F53D0 -- state-2 settle test: walk the n rows and return 1 only
 * when every row's current position already equals its target. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_FieldHudRowsSettled_4f53d0(Obj *p)
{
    u16 id;
    s32 i;
    s32 n;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 v;

    v = p->f378;
    if (v == 0) {
        return 0;
    }
    id = 6;
    if ((s16)v != 2) {
        return 0;
    }
    if (((s32)GetGameData_1fede0()) == 0) {
        return 0;
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        UiGetWidgetPos_2910a0(p, id, &x0, &y0);
        UiGetWidgetTargetPos_290d90(p, id, &x1, &y1);
        if (x0 != x1 || y0 != y1) {
            return 0;
        }
        id += 7;
    }
    return 1;
}
