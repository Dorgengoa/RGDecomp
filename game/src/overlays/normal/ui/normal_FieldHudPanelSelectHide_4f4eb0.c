/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelSelectHide_4f4eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F4EB0 -- the fade twin of 0x004F4DC0: same 3-then-N id walk
 * (10, 17, 24, ... as u16) but through func_2907A0 with 1.0f then 0.0f, and
 * with no NULL guard because func_2907A0 returns void. */

typedef struct Obj { u8 pad000[0x378]; s16 f378; } Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPanelSelectHide_4f4eb0(Obj *p, s32 sel)
{
    u16 id;
    s32 i;
    s32 n;
    s32 k;

    if (p->f378 == 0) {
        return;
    }
    id = 10;
    for (i = 0; i < 3; i++) {
        UiSetWidgetAlpha_2907a0(p, id, 1.0f);
        id += 7;
    }
    GetGameData_1fede0();
    n = normal_FieldHudPartyRowCount_4f9c50();
    id = 10;
    for (k = 0; k < n; k++) {
        if (k == sel) {
            UiSetWidgetAlpha_2907a0(p, id, 0.0f);
        }
        id += 7;
    }
}
