/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogSetMessage_4ee810 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE810 -- forward the parameter to func_28AA30 as a string id
 * and hand the result to slot 8.  The parameter is an s32 id, which is what
 * fixes insmenu_InsectVsConfirmDialogOpen_4ee7c0's parameter type too -- there it is a
 * pass-through and leaves no trace in the object either way. */
extern u8 insmenu_D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */
/*rgp*/
/*rgp*/

void insmenu_InsectVsConfirmDialogSetMessage_4ee810(s32 id)
{
    UiSetTextString_28f510(insmenu_D_004FA180, 8, MsgTableLookup_28aa30(D_004842FC, id), 0);
}
