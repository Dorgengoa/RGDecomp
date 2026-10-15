#include "types.h"
/* normal 0x005211C0 -- guarded teardown; the beql delay slot is the epilogue,
 * so this is a plain `if`, not a shared-return duplication. */

extern s8    D_0048493C;          /* gp - 0x834 */
extern void *D_00484920;          /* gp - 0x850 */

extern void func_291910(void *w);

void normal_ThinkMenuDraw_5211c0(void)
{
    if (D_0048493C != 0) {
        func_291910(D_00484920);
    }
}
