#include "types.h"
/* normal 0x00517CF0 -- the handle is RE-READ after the call (retail's frame is
 * 0x10, no callee-saved register), so the guard load cannot be CSE'd with the
 * argument load: the global is volatile. */

extern void *D_0048478C;                   /* gp - 0x9E4 */
extern void *volatile D_00484784;          /* gp - 0x9EC */

extern void  func_28B0F0(void *w, s32 a);
extern void *func_1F59D0(void);
extern void  func_1CDAE0(void *a, void *b);

s32 normal_TransMenuSubResFree_517cf0(void)
{
    func_28B0F0(D_0048478C, 9);
    if (D_00484784 != NULL) {
        func_1CDAE0(func_1F59D0(), D_00484784);
        D_00484784 = NULL;
    }
    return 1;
}
