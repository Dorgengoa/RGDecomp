/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsYesNoCursorPlace_4ee6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EE6B0 (84 bytes, 21 instructions, 4 calls) -- select the list
 * row and move the cursor widget onto it.  `func_28EC60` returns a record and
 * the two `lh`s off it are the row's x/y, read straight into the call's
 * argument registers.
 */

typedef struct Pos Pos;
struct Pos {
    s16 x;
    s16 y;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsYesNoCursorPlace_4ee6b0(void)
{
    Pos *p;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7532, 1);
    p = ((Pos *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 9, p->x, p->y);
    insmenu_InsectVsYesNoCursorFadeIn_4ee770();
}
