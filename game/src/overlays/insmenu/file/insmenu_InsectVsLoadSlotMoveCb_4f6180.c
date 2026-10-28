/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadSlotMoveCb_4f6180 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F6180 -- three calls on the same object; the parameter is held
 * in $16 because the last of them takes the pointer itself. */

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0x12];
    s16 f12;
    s16 f14;
    s16 f16;
};

/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadSlotMoveCb_4f6180(Obj *o)
{
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->f12);
    insmenu_InsectVsSaveListRefresh_4ebc30(o->f16, 0);
    SaveUiScrollBarThumbPlace_3777a0(o, 0x890C, 1);
    return 1;
}
