/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListMoveCb_4f5050 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F5050 -- the parameter is held in $16 because three of the four
 * calls read it. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct Obj Obj;
struct Obj { u8 pad00[0x12]; s16 f12; s16 f14; s16 f16; };
s32 insmenu_InsectVsTeamListMoveCb_4f5050(Obj *o)
{
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->f12);
    InsectVsTeamListRefreshMaybe_37a2b0(o->f16);
    insmenu_InsectVsTeamListTitleUpdate_4f5400();
    SaveUiScrollBarThumbPlace_3777a0(o, 0x890C, 1);
    return 1;
}
