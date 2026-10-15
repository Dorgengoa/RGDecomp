#include "types.h"
/* normal 0x00524620 -- release the pending handle pair; every path returns 1,
 * and the beql delay slot is the epilogue.  The handle must be a NAMED local
 * off func_1F59D0 -- writing the call inline as the first argument makes mwcc
 * evaluate the gp handle FIRST and burn a callee-saved register on it. */

extern s32 D_004807BC;            /* gp - 0x49B4 */
extern s32 D_004807B8;            /* gp - 0x49B8 */

extern void *func_1F59D0(void);
extern void  func_1CD340(void *p, s32 h);

s32 normal_InsectEntryMenuFileRelease_524620(void)
{
    if (D_004807BC != 0) {
        if (D_004807B8 != -1) {
            void *q = func_1F59D0();
            func_1CD340(q, D_004807B8);
            D_004807BC = 0;
            D_004807B8 = -1;
        }
    }
    return 1;
}
