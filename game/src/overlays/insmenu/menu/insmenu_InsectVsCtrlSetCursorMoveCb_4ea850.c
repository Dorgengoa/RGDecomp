/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsCtrlSetCursorMoveCb_4ea850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EA850 (132 bytes, 33 instructions, 5 calls) -- publish one
 * row's measured extent and its computed total.  `mult $7, $3, $2` is the
 * product written straight into the call's argument register.
 */

typedef struct Row Row;
struct Row {
    u8 pad00[0x6];
    s16 field006;
    u8 pad008[0xA];
    s16 field012;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field024;
};

extern u8 insmenu_D_004FA180[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsCtrlSetCursorMoveCb_4ea850(Row *o, const void *w)
{
    s32 sp3C;
    s32 sp38;

    GetGridCellPos_28ed30(o, &sp3C, &sp38);
    UiSetWidgetPos_290f60(w, 0xE, sp3C, sp38);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0xB, 0, o->field012 * o->field006);
    RecordSetSubState_430bd0(((Handle *)GetGameData_1fede0())->field024, o->field012);
    return 1;
}
