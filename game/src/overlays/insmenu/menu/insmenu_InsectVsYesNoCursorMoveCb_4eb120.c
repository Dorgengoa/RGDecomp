/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsYesNoCursorMoveCb_4eb120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EB120 (100 bytes, 25 instructions, 2 calls) -- the same row
 * push as insmenu_InsectVsSaveConfirmMoveCb_4f6ed0 with the widget taken as a parameter and a
 * different field id.  Same negated-inequality bool for the last argument.
 */

typedef struct Row Row;
struct Row {
    u8 pad00[0x10];
    s16 field010;
};

/*rgp*/

s32 insmenu_InsectVsYesNoCursorMoveCb_4eb120(Row *o, const void *w)
{
    u8 b;

    UiSetSpriteU_28f930(w, 8, 0x7A, o->field010);
    b = !(o->field010 != 0);
    UiSetSpriteU_28f930(w, 8, 0x46, b);
    return 1;
}
