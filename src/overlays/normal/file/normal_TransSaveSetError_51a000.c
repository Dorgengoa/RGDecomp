#include "types.h"
/* normal 0x0051A000 -- store then tail call.  The gp load of D_004847D0 sits
 * AFTER the `sh` in retail, which is the recorded "a gp load will not move
 * above a store" ordering: the store is written first in source. */

extern s16   D_004847FC;          /* gp - 0x974 */
extern void *D_004847D0;          /* gp - 0x9A0 */

extern void func_28EDE0(void *p, s32 id, s32 a);

void normal_TransSaveSetError_51a000(s32 a)
{
    D_004847FC = a;
    func_28EDE0(D_004847D0, 0xA, 0);
}
