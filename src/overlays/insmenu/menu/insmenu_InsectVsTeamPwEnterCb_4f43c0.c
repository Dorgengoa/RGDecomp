#include "types.h"
/* insmenu 0x004F43C0 -- feed one call's result straight into the next
 * (`daddu $4, $2, $0` in the second jal's delay slot), return 1. */
extern void *insmenu_InsectVsTeamListGetSelRec_4f93b0(void);
extern void func_379000(void *a, s32 b);
s32 insmenu_InsectVsTeamPwEnterCb_4f43c0(void)
{
    func_379000(insmenu_InsectVsTeamListGetSelRec_4f93b0(), 1);
    return 1;
}
