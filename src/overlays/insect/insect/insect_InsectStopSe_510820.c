#include "types.h"
/* insect 0x00510820 -- 18 instructions.  The call result lands straight in $4
 * and is tested there, so it is the first argument of the inner call. */

extern void  func_1D0590(void *h, s32 id);
extern void *func_1F5BE0(void);

void insect_InsectStopSe_510820(s32 id)
{
    void *h;

    if (id != -1) {
        h = func_1F5BE0();
        if (h != 0) {
            func_1D0590(h, id);
        }
    }
}
