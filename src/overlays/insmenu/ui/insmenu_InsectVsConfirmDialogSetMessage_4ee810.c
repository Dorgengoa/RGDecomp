#include "types.h"
/* insmenu 0x004EE810 -- forward the parameter to func_28AA30 as a string id
 * and hand the result to slot 8.  The parameter is an s32 id, which is what
 * fixes insmenu_InsectVsConfirmDialogOpen_4ee7c0's parameter type too -- there it is a
 * pass-through and leaves no trace in the object either way. */
extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);

void insmenu_InsectVsConfirmDialogSetMessage_4ee810(s32 id)
{
    func_28F510(D_004FA180, 8, func_28AA30(D_004842FC, id), 0);
}
